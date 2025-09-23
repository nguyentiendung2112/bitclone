//
// Created by Dung on 14/9/25.
//

#ifndef FILEENTRY_H
#define FILEENTRY_H
#include <string>

#include "byte_buffer/BytesBuffer.h"


class FileEntry {
  time_t timestamp;
  BytesBuffer key = BytesBuffer();
  BytesBuffer value = BytesBuffer();
  public:
    FileEntry(const time_t timestamp, const BytesBuffer key, const BytesBuffer value) {
      this->timestamp = timestamp;
      this->key = key;
      this->value = value;
    }
    BytesBuffer getKey();
    BytesBuffer getValue();
    std::string getKeyStr();
    std::string getValueStr();
};

#endif //FILEENTRY_H
