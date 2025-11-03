//
// Created by Dung on 14/9/25.
//

#ifndef LOGWRITER_H
#define LOGWRITER_H
#include <string>
#include <unistd.h>

#include "src/byte_buffer/BytesBuffer.h"


class LogWriter{
  std::string filePath;
  int fileDescriptor;

  public:
    LogWriter(const std::string& filePath, int fileDescriptor) {
      this -> filePath = filePath;
      this -> fileDescriptor = fileDescriptor;
    }

    void append(BytesBuffer* bytesBuffer) const {
      off_t offset = lseek(this->fileDescriptor, 0, SEEK_END);
      if (offset == (off_t) -1) {
        throw std::runtime_error("Failed to find offset");
      }
      auto res = write(this->fileDescriptor, bytesBuffer->getBuffer(), bytesBuffer->getSize());
      if (res<0) {
        throw std::runtime_error("Failed to append file");
      }
    }
};


#endif //LOGWRITER_H
