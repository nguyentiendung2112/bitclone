//
// Created by Dung on 14/9/25.
//

#ifndef LOGREADER_H
#define LOGREADER_H

#include <ios>

#include <fcntl.h>
#include <unistd.h>

#include "src/byte_buffer/BytesBuffer.h"

using namespace std;

class LogReader{
  string filePath;
  int fileDescriptor;

  public:
  BytesBuffer* at(uint64_t pos, size_t size) const;
  LogReader(const string& filePath, int fileDescriptor) {
    this -> filePath = filePath;
    this -> fileDescriptor = fileDescriptor;
  }

};

inline BytesBuffer* LogReader::at(uint64_t pos, size_t size) const {
  auto* bytes_buffer = new BytesBuffer(new byte[size], size);
  auto result = pread(this->fileDescriptor, (void *)bytes_buffer->getBuffer(), bytes_buffer->getSize(), pos);
  if (result != size) {
    throw std::runtime_error("failed to read file");
  }
  return  bytes_buffer;
}




#endif //LOGREADER_H
