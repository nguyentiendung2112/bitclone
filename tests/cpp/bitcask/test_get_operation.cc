#include "gtest/gtest.h"
#include "src/bitcask/BitcaskStore.h"
#include <filesystem>

namespace {

class GetOperationTest : public ::testing::Test {
protected:
    std::string test_dir;
    
    void SetUp() override {
        test_dir = "/tmp/get_test_" + std::to_string(std::chrono::system_clock::now().time_since_epoch().count());
    }
    
    void TearDown() override {
        std::filesystem::remove_all(test_dir);
    }
};

TEST_F(GetOperationTest, GetExistingKey) {
    BitcaskStore store(test_dir);
}

TEST_F(GetOperationTest, GetMissingKey) {
    BitcaskStore store(test_dir);
}

TEST_F(GetOperationTest, GetAfterOverwrite) {
    BitcaskStore store(test_dir);
}

TEST_F(GetOperationTest, GetAfterDelete) {
    BitcaskStore store(test_dir);
}

TEST_F(GetOperationTest, ConcurrentGets) {
    BitcaskStore store(test_dir);
}

}
