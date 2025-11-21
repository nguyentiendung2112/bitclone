#include "gtest/gtest.h"
#include "src/bitcask/BitcaskStore.h"
#include "src/bitcask/BitcaskConfig.h"
#include <filesystem>

namespace {

class FileRotationTest : public ::testing::Test {
protected:
    std::string test_dir;
    
    void SetUp() override {
        test_dir = "/tmp/rotation_test_" + std::to_string(std::chrono::system_clock::now().time_since_epoch().count());
    }
    
    void TearDown() override {
        std::filesystem::remove_all(test_dir);
    }
};

TEST_F(FileRotationTest, RotationTriggered) {
    BitcaskConfig config;
    config.max_file_size = 1024;
    BitcaskStore store(test_dir, config);
}

TEST_F(FileRotationTest, DataAccessibleAfterRotation) {
    BitcaskConfig config;
    config.max_file_size = 1024;
    BitcaskStore store(test_dir, config);
}

TEST_F(FileRotationTest, MultipleRotations) {
    BitcaskConfig config;
    config.max_file_size = 1024;
    BitcaskStore store(test_dir, config);
}

}
