//
// Created by Dung on 5/11/25.
//

#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include <unistd.h>

#include "src/byte_buffer/BytesBuffer.h"

using namespace std;

class FileHandler {
  public:
    static std::vector<std::byte> readAt(int fileDescriptor,uint64_t pos, size_t size) {
      auto* bytes_buffer = new BytesBuffer(new std::byte[size], size);
      auto result = pread(fileDescriptor, (void *)bytes_buffer->getBuffer(), bytes_buffer->getSize(), pos);
      if (result != size) {
        throw std::runtime_error("failed to read file");
      }
      return  bytes_buffer;
    }
};

#endif //FILEHANDLER_H
