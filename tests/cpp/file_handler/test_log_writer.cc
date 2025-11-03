//
// Created by Dung on 2/11/25.
//

#include <fstream>

#include "gtest/gtest.h"
#include "src/file_handler/LogWriter.h"
#include <memory>
#include <sys/fcntl.h>

#include "src/file_handler/LogReader.h"

namespace TestLogWriter {
TEST(LogWriter, append) {
  auto filePath = "tests/resources/filewrite000";
  std::ofstream outputFile(filePath);
  outputFile << "123456";
  outputFile.close();
  auto fd = open(filePath, O_WRONLY);
  LogWriter logWriter =  LogWriter(filePath, fd);
  const char* buffer = "789";
  auto* byteB = new BytesBuffer(reinterpret_cast<const std::byte *>(buffer), 3);
  std::cout << byteB->str();
  std::unique_ptr<BytesBuffer> bytesBuffer(byteB);
  logWriter.append(byteB);
  close(fd);
  fd = open(filePath, O_RDONLY);
  LogReader logReader = LogReader(filePath, fd);
  std::unique_ptr<BytesBuffer> bytesBufferRead(logReader.at(0, 9));
  EXPECT_EQ(bytesBufferRead->str(), "\"123456789\"");

}
}
