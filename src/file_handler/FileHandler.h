//
// Created by Dung on 5/11/25.
//

#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <cstddef>
#include <stdexcept>
#include <unistd.h>
#include <vector>


class FileHandler {
  public:
    static std::vector<std::byte> readAt(int file_descriptor, std::uint64_t pos, std::size_t size) {
      std::vector<std::byte> bytes_buffer(size);
      ssize_t result = pread(file_descriptor,
                             bytes_buffer.data(),
                             bytes_buffer.size(),
                             static_cast<off_t>(pos));
      if (result != static_cast<ssize_t>(size)) {
        throw std::runtime_error("failed to read file");
      }
      return bytes_buffer;
    }

    static void append(int file_descriptor, const std::vector<std::byte> &buffer) {
      const off_t offset = lseek(file_descriptor, 0, SEEK_END);
      if (offset == static_cast<off_t>(-1)) {
        throw std::runtime_error("Failed to find offset");
      }
      const auto res = pwrite(file_descriptor, buffer.data(), buffer.size(), offset);
      if (res < 0) {
        throw std::runtime_error("Failed to append file");
      }
      fsync(file_descriptor);
    }
};


#endif  // FILEHANDLER_H
