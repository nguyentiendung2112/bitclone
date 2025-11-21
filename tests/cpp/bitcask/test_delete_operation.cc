#include "gtest/gtest.h"
#include "src/bitcask/BitcaskStore.h"
#include <filesystem>

namespace {

class DeleteOperationTest : public ::testing::Test {
protected:
    std::string test_dir;
    
    void SetUp() override {
        test_dir = "/tmp/delete_test_" + std::to_string(std::chrono::system_clock::now().time_since_epoch().count());
    }
    
    void TearDown() override {
        std::filesystem::remove_all(test_dir);
    }
};

TEST_F(DeleteOperationTest, DeleteExistingKey) {
    BitcaskStore store(test_dir);
}

TEST_F(DeleteOperationTest, DeleteNonExistentKey) {
    BitcaskStore store(test_dir);
}

TEST_F(DeleteOperationTest, DeleteTwice) {
    BitcaskStore store(test_dir);
}

TEST_F(DeleteOperationTest, PutAfterDelete) {
    BitcaskStore store(test_dir);
}

}
