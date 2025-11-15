//
// Created by Dung on 14/9/25.
//

#ifndef LOGREADER_H
#define LOGREADER_H

#include <cstddef>

#include <string>

#include <unistd.h>
#include <vector>

#include "FileHandler.h"
#include "LogIndex.h"

class LogReader {
  static std::unique_ptr<LogIndex> deserialize(std::vector<std::byte> &data) {
    size_t pos = 0;
    uint64_t key_size = 0, value_size = 0;

    std::memcpy(&key_size, data.data() + pos, sizeof(uint64_t));
    pos += sizeof(uint64_t);
    std::memcpy(&value_size, data.data() + pos, sizeof(uint64_t));
    pos += sizeof(uint64_t);
    std::string key(reinterpret_cast<const char *>(data.data() + pos), key_size);
    pos += key_size;
    std::string value(reinterpret_cast<const char *>(data.data() + pos), value_size);
    return std::make_unique<LogIndex>(key, value);
  }

  public:
    LogReader() = default;

    static std::unique_ptr<LogIndex> readRecordAt(int file_descriptor, size_t pos) {
      std::vector<std::byte> header = FileHandler::readAt(file_descriptor, pos, sizeof(uint64_t) * 2);
      uint64_t key_size = 0, value_size = 0;
      std::memcpy(&key_size, header.data(), sizeof(uint64_t));
      std::memcpy(&value_size, header.data() + sizeof(key_size), sizeof(uint64_t));
      size_t total_size = sizeof(key_size) + sizeof(value_size) + key_size + value_size;
      std::vector<std::byte> record = FileHandler::readAt(file_descriptor, pos, total_size);
      return deserialize(record);
    }
};

#endif  // LOGREADER_H
