//
// Created by Dung on 14/9/25.
//

#ifndef BYTESBUFFER_H
#define BYTESBUFFER_H


#include <cstddef>
#include <string>

class BytesBuffer {
  std::byte* buffer;
  long size;
  public:
    BytesBuffer(std::byte* buffer, long size) {
      this->buffer = buffer;
      this->size = size;
    }
    BytesBuffer() {
      this->buffer = nullptr;
      this->size = 0;
    }

    std::string decode();

    BytesBuffer fromString(const std::string& str);

    ~BytesBuffer() {
        delete[] this->buffer;
    }
};





#endif //BYTESBUFFER_H
