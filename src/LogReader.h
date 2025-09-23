//
// Created by Dung on 14/9/25.
//

#ifndef LOGREADER_H
#define LOGREADER_H
#include <cstdint>

#include "LogIndex.h"
#include "byte_buffer/BytesBuffer.h"


class LogReader {
  BytesBuffer at(LogIndex logIndex);
};



#endif //LOGREADER_H
