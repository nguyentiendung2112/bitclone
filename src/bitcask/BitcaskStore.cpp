#include "BitcaskStore.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <chrono>
#include <iomanip>
#include <sstream>
#include "src/file_handler/LogWriter.h"
#include "src/file_handler/LogReader.h"
#include "src/file_handler/FileHandler.h"

BitcaskStore::BitcaskStore(const std::string& directory)
    : BitcaskStore(directory, BitcaskConfig()) {}

BitcaskStore::BitcaskStore(const std::string& directory, const BitcaskConfig& config)
    : config_(config), next_file_id_(1) {
    config_.directory = directory;
    mkdir(config_.directory.c_str(), 0755);
    std::string initial_path = generateFilePath(next_file_id_);
    int fd = openFile(initial_path, true);
    active_file_ = FileMetadata(next_file_id_, initial_path, fd, 0);
    next_file_id_++;
}

BitcaskStore::~BitcaskStore() {
    if (active_file_.file_descriptor >= 0) {
        closeFile(active_file_.file_descriptor);
    }
}

std::string BitcaskStore::generateFilePath(std::uint64_t file_id) {
    std::ostringstream oss;
    oss << config_.directory << "/" << std::setw(20) << std::setfill('0') << file_id << config_.file_extension;
    return oss.str();
}

int BitcaskStore::openFile(const std::string& path, bool create) {
    int flags = O_RDWR;
    if (create) {
        flags |= O_CREAT;
    }
    int fd = open(path.c_str(), flags, 0644);
    return fd;
}

void BitcaskStore::closeFile(int fd) {
    if (fd >= 0) {
        close(fd);
    }
}

bool BitcaskStore::syncFile(int fd) {
    if (fd >= 0) {
        return fsync(fd) == 0;
    }
    return false;
}

std::uint64_t BitcaskStore::getCurrentTimestamp() const {
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::seconds>(duration).count();
}

bool BitcaskStore::needsRotation() const {
    return active_file_.current_size >= config_.max_file_size;
}

bool BitcaskStore::rotateFile() {
    if (active_file_.file_descriptor >= 0) {
        syncFile(active_file_.file_descriptor);
        closeFile(active_file_.file_descriptor);
    }
    std::string new_path = generateFilePath(next_file_id_);
    int new_fd = openFile(new_path, true);
    if (new_fd < 0) {
        return false;
    }
    active_file_ = FileMetadata(next_file_id_, new_path, new_fd, 0);
    next_file_id_++;
    return true;
}

bool BitcaskStore::put(const std::string& key, const std::byte* value, std::size_t value_size) {
    std::lock_guard<std::mutex> lock(write_mutex_);
    
    if (active_file_.file_descriptor < 0) {
        return false;
    }
    
    std::uint64_t value_pos = active_file_.current_size;
    std::uint64_t timestamp = getCurrentTimestamp();
    
    try {
        LogWriter::appendRecord(active_file_.file_descriptor, key, const_cast<std::byte*>(value), value_size);
    } catch (...) {
        return false;
    }
    
    off_t new_size = lseek(active_file_.file_descriptor, 0, SEEK_END);
    if (new_size < 0) {
        return false;
    }
    active_file_.current_size = static_cast<std::uint64_t>(new_size);
    
    KeyDirEntry entry(active_file_.file_id, active_file_.file_path, value_pos, value_size, timestamp);
    keydir_.put(key, entry);
    
    if (config_.fsync_each_write) {
        syncFile(active_file_.file_descriptor);
    }
    
    if (needsRotation()) {
        rotateFile();
    }
    
    return true;
}

std::optional<std::vector<std::byte>> BitcaskStore::get(const std::string& key) const {
    auto entry_opt = keydir_.get(key);
    if (!entry_opt.has_value()) {
        return std::nullopt;
    }
    
    KeyDirEntry entry = entry_opt.value();
    int fd = openFile(entry.file_path, false);
    if (fd < 0) {
        return std::nullopt;
    }
    
    try {
        auto record = LogReader::readRecordAt(fd, entry.value_pos);
        closeFile(fd);
        
        if (!record) {
            return std::nullopt;
        }
        
        std::vector<std::byte> value_bytes(record->value.size());
        std::memcpy(value_bytes.data(), record->value.data(), record->value.size());
        return value_bytes;
    } catch (...) {
        closeFile(fd);
        return std::nullopt;
    }
}

bool BitcaskStore::del(const std::string& key) {
    std::lock_guard<std::mutex> lock(write_mutex_);
    
    if (!keydir_.has(key)) {
        return false;
    }
    
    try {
        LogWriter::appendRecord(active_file_.file_descriptor, key, nullptr, 0);
    } catch (...) {
        return false;
    }
    
    keydir_.remove(key);
    
    if (config_.fsync_each_write) {
        syncFile(active_file_.file_descriptor);
    }
    
    return true;
}

bool BitcaskStore::sync() {
    std::lock_guard<std::mutex> lock(write_mutex_);
    return syncFile(active_file_.file_descriptor);
}

StoreStats BitcaskStore::getStats() const {
    StoreStats stats;
    stats.total_keys = keydir_.size();
    stats.active_file_size = active_file_.current_size;
    stats.total_files = next_file_id_ - 1;
    return stats;
}
