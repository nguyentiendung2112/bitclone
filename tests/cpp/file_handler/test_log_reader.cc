#include "gtest/gtest.h"
#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <string>
#include <vector>
#include "src/file_handler/LogWriter.h"
#include "src/file_handler/LogReader.h"
#include "src/file_handler/LogIndex.h"

class LogReaderTest : public ::testing::Test {
protected:
    char filename[32];
    int fd;

    void SetUp() override {
        std::snprintf(filename, sizeof(filename), "/tmp/logreader_testXXXXXX");
        fd = mkstemp(filename);
        ASSERT_NE(fd, -1);
    }

    void TearDown() override {
        close(fd);
        std::remove(filename);
    }
};

TEST_F(LogReaderTest, WriteAndReadRecord) {
    std::string key = "foo";
    std::string value = "bar";
    LogWriter::appendRecord(fd, key, reinterpret_cast<std::byte*>(value.data()), value.size());

    auto logIndex = LogReader<std::string, std::string>::readRecordAt(fd, 0);
    ASSERT_EQ(logIndex->key, key);
    ASSERT_EQ(logIndex->value, value);
}//
// Created by Dung on 15/11/25.
//
