//
// Created by Dung on 14/9/25.
//

#include "LogWriter.h"

#include "FileEntry.h"

LogIndex LogWriter::append(FileEntry) {
  return LogIndex(0,0);
}
