//
// Created by Copilot on 15/11/25.
//

#ifndef KEYDIRENTRY_H
#define KEYDIRENTRY_H

#include <cstdint>
#include <string>

struct KeyDirEntry {
  std::uint64_t file_id;
  std::string file_path;
  std::uint64_t value_pos;
  std::uint64_t value_size;
  std::uint64_t timestamp;

  KeyDirEntry() = default;

  KeyDirEntry(std::uint64_t file_id, std::string file_path,
              std::uint64_t value_pos, std::uint64_t value_size,
              std::uint64_t timestamp)
      : file_id(file_id),
        file_path(std::move(file_path)),
        value_pos(value_pos),
        value_size(value_size),
        timestamp(timestamp) {}
};

#endif  // KEYDIRENTRY_H
