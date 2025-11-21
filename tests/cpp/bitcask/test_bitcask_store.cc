#include "gtest/gtest.h"
#include "src/bitcask/BitcaskStore.h"
#include <filesystem>
#include <vector>

namespace {

class BitcaskStoreTest : public ::testing::Test {
protected:
    std::string test_dir;
    
    void SetUp() override {
        test_dir = "/tmp/bitcask_test_" + std::to_string(std::chrono::system_clock::now().time_since_epoch().count());
    }
    
    void TearDown() override {
        std::filesystem::remove_all(test_dir);
    }
};

TEST_F(BitcaskStoreTest, ConstructorCreatesDirectory) {
    BitcaskStore store(test_dir);
    EXPECT_TRUE(std::filesystem::exists(test_dir));
}

TEST_F(BitcaskStoreTest, PutAndGetSingleKey) {
    BitcaskStore store(test_dir);
    std::string key = "test_key";
    std::vector<std::byte> value = {std::byte(1), std::byte(2), std::byte(3)};
    
    bool put_result = store.put(key, value.data(), value.size());
    EXPECT_TRUE(put_result);
    
    auto get_result = store.get(key);
    ASSERT_TRUE(get_result.has_value());
    EXPECT_EQ(get_result.value(), value);
}

TEST_F(BitcaskStoreTest, GetNonExistentKey) {
    BitcaskStore store(test_dir);
    auto result = store.get("nonexistent");
    EXPECT_FALSE(result.has_value());
}

TEST_F(BitcaskStoreTest, OverwriteKey) {
    BitcaskStore store(test_dir);
    std::string key = "test_key";
    std::vector<std::byte> value1 = {std::byte(1), std::byte(2)};
    std::vector<std::byte> value2 = {std::byte(3), std::byte(4), std::byte(5)};
    
    store.put(key, value1.data(), value1.size());
    store.put(key, value2.data(), value2.size());
    
    auto result = store.get(key);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value(), value2);
}

TEST_F(BitcaskStoreTest, DeleteKey) {
    BitcaskStore store(test_dir);
    std::string key = "test_key";
    std::vector<std::byte> value = {std::byte(1), std::byte(2)};
    
    store.put(key, value.data(), value.size());
    bool del_result = store.del(key);
    EXPECT_TRUE(del_result);
    
    auto get_result = store.get(key);
    EXPECT_FALSE(get_result.has_value());
}

TEST_F(BitcaskStoreTest, DeleteNonExistentKey) {
    BitcaskStore store(test_dir);
    bool result = store.del("nonexistent");
    EXPECT_FALSE(result);
}

TEST_F(BitcaskStoreTest, MultipleKeys) {
    BitcaskStore store(test_dir);
    
    for (int i = 0; i < 100; ++i) {
        std::string key = "key_" + std::to_string(i);
        std::vector<std::byte> value = {std::byte(i % 256)};
        store.put(key, value.data(), value.size());
    }
    
    for (int i = 0; i < 100; ++i) {
        std::string key = "key_" + std::to_string(i);
        auto result = store.get(key);
        ASSERT_TRUE(result.has_value());
        EXPECT_EQ(result.value()[0], std::byte(i % 256));
    }
}

TEST_F(BitcaskStoreTest, EmptyValue) {
    BitcaskStore store(test_dir);
    std::string key = "empty_key";
    std::vector<std::byte> value = {};
    
    bool put_result = store.put(key, value.data(), 0);
    EXPECT_TRUE(put_result);
    
    auto get_result = store.get(key);
    ASSERT_TRUE(get_result.has_value());
    EXPECT_TRUE(get_result.value().empty());
}

TEST_F(BitcaskStoreTest, LargeValue) {
    BitcaskStore store(test_dir);
    std::string key = "large_key";
    std::vector<std::byte> value(1024 * 1024);
    for (size_t i = 0; i < value.size(); ++i) {
        value[i] = std::byte(i % 256);
    }
    
    bool put_result = store.put(key, value.data(), value.size());
    EXPECT_TRUE(put_result);
    
    auto get_result = store.get(key);
    ASSERT_TRUE(get_result.has_value());
    EXPECT_EQ(get_result.value(), value);
}

TEST_F(BitcaskStoreTest, StatsTracking) {
    BitcaskStore store(test_dir);
    auto stats1 = store.getStats();
    EXPECT_EQ(stats1.total_keys, 0);
    
    std::string key = "test_key";
    std::vector<std::byte> value = {std::byte(1), std::byte(2)};
    store.put(key, value.data(), value.size());
    
    auto stats2 = store.getStats();
    EXPECT_EQ(stats2.total_keys, 1);
}

TEST_F(BitcaskStoreTest, SyncOperation) {
    BitcaskStore store(test_dir);
    std::string key = "test_key";
    std::vector<std::byte> value = {std::byte(1), std::byte(2)};
    
    store.put(key, value.data(), value.size());
    bool sync_result = store.sync();
    EXPECT_TRUE(sync_result);
}

}
