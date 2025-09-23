//
// Created by Dung on 14/9/25.
//

#ifndef LOGWRITER_H
#define LOGWRITER_H

#include "FileEntry.h"
#include "LogIndex.h"

class LogWriter {
  public:
    LogWriter() = default;
    LogIndex append(FileEntry index);
};



#endif //LOGWRITER_H
