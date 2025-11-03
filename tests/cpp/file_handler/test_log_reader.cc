#include "gtest/gtest.h"
#include "src/file_handler/LogReader.h"
#include <memory>

namespace TestLogReader {
  TEST(LogReader, readAt) {
    auto filePath = "tests/resources/file000";
    auto fd = open(filePath, O_RDONLY);
    LogReader logReader =  LogReader(filePath, fd);
    std::unique_ptr<BytesBuffer> bytesBuffer(logReader.at(3, 4));
    EXPECT_EQ(bytesBuffer->str(), "\"4567\"");
  }
}