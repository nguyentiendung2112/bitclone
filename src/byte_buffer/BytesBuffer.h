//
// Created by Dung on 14/9/25.
//

#ifndef BYTESBUFFER_H
#define BYTESBUFFER_H


#include <cstddef>
#include <string>

class BytesBuffer {
  const std::byte* buffer;
  long size;
  public:
    BytesBuffer(const std::byte* buffer, long size) {
      this->buffer = buffer;
      this->size = size;
    }

    ~BytesBuffer() {
    }

    [[nodiscard]] const std::byte * getBuffer() const {
      return buffer;
    }
    [[nodiscard]] long getSize() const {
      return size;
    }
    // debug
    std::string str() {
      return ("\""+std::string(reinterpret_cast<const char *>(this->buffer))+ "\"");
    }
};





#endif //BYTESBUFFER_H
