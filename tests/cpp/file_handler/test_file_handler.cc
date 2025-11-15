//
// Created by Dung on 7/11/25.
//

#include <gtest/gtest.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <vector>

#include "src/file_handler/FileHandler.h"

namespace FileHandlerTest {
  TEST(FileHandler, appendAndReadAt) {
    char filename[] = "filehandler_testXXXXXX";
    int fd = mkstemp(filename);
    ASSERT_NE(fd, -1);

    std::string test_str = "dung vip pro";
    std::vector<std::byte> buffer(reinterpret_cast<const std::byte*>(test_str.data()),
                              reinterpret_cast<const std::byte*>(test_str.data() + test_str.size()));

  // Append data
    FileHandler::append(fd, buffer);
    std::vector<std::byte> read_buffer = FileHandler::readAt(fd, 0, buffer.size());
    std::string result(reinterpret_cast<const char*>(read_buffer.data()), read_buffer.size());
    EXPECT_EQ(result, test_str);
    close(fd);
    std::remove(filename);
  }
}
