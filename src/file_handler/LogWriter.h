//
// Created by Dung on 14/9/25.
//

#ifndef LOGWRITER_H
#define LOGWRITER_H

#include <cstddef>
#include <string>
#include <unistd.h>

#include "FileHandler.h"


using namespace std;

class LogWriter {
  static std::vector<byte> serialize(string key, std::byte *value, size_t value_size) {
    // layout [uint64_t key_size][uint64_t value_size][key bytes][value bytes]

    auto key_size = static_cast<uint64_t>(key.size());
    auto val_size = static_cast<uint64_t>(value_size);

    const size_t header_size = sizeof(key_size) + sizeof(val_size);
    const size_t total_size = header_size + key.size() + value_size;

    std::vector<std::byte> out;
    out.resize(total_size);

    size_t pos = 0;

    // write key size
    std::memcpy(out.data() + pos, &key_size, sizeof(key_size));
    pos += sizeof(key_size);
    // write value size
    std::memcpy(out.data() + pos, &val_size, sizeof(val_size));
    pos += sizeof(val_size);

    // write key bytes
    if (!key.empty()) {
      std::memcpy(out.data() + pos, key.data(), key.size());
      pos += key_size;
    }
    if (value != nullptr && value_size > 0) {
      std::memcpy(out.data() + pos, value, value_size);
    }

    return out;
  }

  public:
    LogWriter() = default;

    static void appendRecord(int file_descriptor, const string &key, std::byte *value, const size_t value_size) {
      if (file_descriptor < 0) {
        throw std::runtime_error("invalid file descriptor");
      }
      std::vector<std::byte> buf = serialize(key, value, value_size);
      FileHandler::append(file_descriptor, buf);
    }
};

#endif  // LOGWRITER_H
