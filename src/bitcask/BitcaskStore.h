#ifndef BITCASKSTORE_H
#define BITCASKSTORE_H

#include <cstddef>
#include <optional>
#include <string>
#include <vector>
#include <mutex>

#include "BitcaskConfig.h"
#include "FileMetadata.h"
#include "StoreStats.h"
#include "src/keydir/KeyDir.h"

class BitcaskStore {
private:
    BitcaskConfig config_;
    KeyDir keydir_;
    FileMetadata active_file_;
    std::uint64_t next_file_id_;
    std::mutex write_mutex_;
    
    std::string generateFilePath(std::uint64_t file_id);
    bool rotateFile();
    bool needsRotation() const;
    int openFile(const std::string& path, bool create);
    void closeFile(int fd);
    std::uint64_t getCurrentTimestamp() const;
    bool syncFile(int fd);
    
public:
    explicit BitcaskStore(const std::string& directory);
    BitcaskStore(const std::string& directory, const BitcaskConfig& config);
    
    bool put(const std::string& key, const std::byte* value, std::size_t value_size);
    std::optional<std::vector<std::byte>> get(const std::string& key) const;
    bool del(const std::string& key);
    bool sync();
    StoreStats getStats() const;
    
    ~BitcaskStore();
};

#endif
