//
// Created by Copilot on 15/11/25.
//
#include "gtest/gtest.h"
#include "src/keydir/KeyDir.h"
#include "src/keydir/KeyDirEntry.h"

namespace {

TEST(KeyDir, PutAndGet) {
  KeyDir keydir;
  KeyDirEntry entry(1, "/path/to/file1.data", 0, 100, 1234567890);

  keydir.put("key1", entry);

  auto result = keydir.get("key1");
  ASSERT_TRUE(result.has_value());
  EXPECT_EQ(result->file_id, 1);
  EXPECT_EQ(result->file_path, "/path/to/file1.data");
  EXPECT_EQ(result->value_pos, 0);
  EXPECT_EQ(result->value_size, 100);
  EXPECT_EQ(result->timestamp, 1234567890);
}

TEST(KeyDir, GetNonExistentKey) {
  KeyDir keydir;
  auto result = keydir.get("nonexistent");
  EXPECT_FALSE(result.has_value());
}

TEST(KeyDir, UpdateExistingKey) {
  KeyDir keydir;
  KeyDirEntry entry1(1, "/path/to/file1.data", 0, 100, 1234567890);
  KeyDirEntry entry2(2, "/path/to/file2.data", 200, 150, 1234567900);

  keydir.put("key1", entry1);
  keydir.put("key1", entry2);

  auto result = keydir.get("key1");
  ASSERT_TRUE(result.has_value());
  EXPECT_EQ(result->file_id, 2);
  EXPECT_EQ(result->file_path, "/path/to/file2.data");
  EXPECT_EQ(result->value_pos, 200);
  EXPECT_EQ(result->value_size, 150);
  EXPECT_EQ(result->timestamp, 1234567900);
}

TEST(KeyDir, Has) {
  KeyDir keydir;
  KeyDirEntry entry(1, "/path/to/file1.data", 0, 100, 1234567890);

  EXPECT_FALSE(keydir.has("key1"));
  keydir.put("key1", entry);
  EXPECT_TRUE(keydir.has("key1"));
  EXPECT_FALSE(keydir.has("key2"));
}

TEST(KeyDir, Remove) {
  KeyDir keydir;
  KeyDirEntry entry(1, "/path/to/file1.data", 0, 100, 1234567890);

  keydir.put("key1", entry);
  EXPECT_TRUE(keydir.has("key1"));

  keydir.remove("key1");
  EXPECT_FALSE(keydir.has("key1"));

  auto result = keydir.get("key1");
  EXPECT_FALSE(result.has_value());
}

TEST(KeyDir, RemoveNonExistentKey) {
  KeyDir keydir;
  // Should not crash when removing non-existent key
  keydir.remove("nonexistent");
  EXPECT_FALSE(keydir.has("nonexistent"));
}

TEST(KeyDir, Size) {
  KeyDir keydir;
  EXPECT_EQ(keydir.size(), 0);

  KeyDirEntry entry1(1, "/path/to/file1.data", 0, 100, 1234567890);
  KeyDirEntry entry2(2, "/path/to/file2.data", 100, 200, 1234567900);

  keydir.put("key1", entry1);
  EXPECT_EQ(keydir.size(), 1);

  keydir.put("key2", entry2);
  EXPECT_EQ(keydir.size(), 2);

  keydir.put("key1", entry2);  // update existing key
  EXPECT_EQ(keydir.size(), 2);

  keydir.remove("key1");
  EXPECT_EQ(keydir.size(), 1);
}

TEST(KeyDir, Clear) {
  KeyDir keydir;
  KeyDirEntry entry1(1, "/path/to/file1.data", 0, 100, 1234567890);
  KeyDirEntry entry2(2, "/path/to/file2.data", 100, 200, 1234567900);

  keydir.put("key1", entry1);
  keydir.put("key2", entry2);
  EXPECT_EQ(keydir.size(), 2);

  keydir.clear();
  EXPECT_EQ(keydir.size(), 0);
  EXPECT_FALSE(keydir.has("key1"));
  EXPECT_FALSE(keydir.has("key2"));
}

TEST(KeyDir, MultipleKeys) {
  KeyDir keydir;

  for (int i = 0; i < 100; ++i) {
    std::string key = "key" + std::to_string(i);
    KeyDirEntry entry(i, "/path/to/file" + std::to_string(i) + ".data", i * 100,
                      100, 1234567890 + i);
    keydir.put(key, entry);
  }

  EXPECT_EQ(keydir.size(), 100);

  for (int i = 0; i < 100; ++i) {
    std::string key = "key" + std::to_string(i);
    EXPECT_TRUE(keydir.has(key));

    auto result = keydir.get(key);
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->file_id, i);
    EXPECT_EQ(result->value_pos, i * 100);
  }
}

TEST(KeyDir, EmptyStringKey) {
  KeyDir keydir;
  KeyDirEntry entry(1, "/path/to/file1.data", 0, 100, 1234567890);

  keydir.put("", entry);
  EXPECT_TRUE(keydir.has(""));

  auto result = keydir.get("");
  ASSERT_TRUE(result.has_value());
  EXPECT_EQ(result->file_id, 1);
}

TEST(KeyDir, LongKey) {
  KeyDir keydir;
  std::string long_key(1000, 'a');
  KeyDirEntry entry(1, "/path/to/file1.data", 0, 100, 1234567890);

  keydir.put(long_key, entry);
  EXPECT_TRUE(keydir.has(long_key));

  auto result = keydir.get(long_key);
  ASSERT_TRUE(result.has_value());
  EXPECT_EQ(result->file_id, 1);
}

TEST(KeyDirEntry, DefaultConstructor) {
  KeyDirEntry entry;
  // Should compile and not crash
  EXPECT_EQ(entry.file_id, 0);
  EXPECT_EQ(entry.value_pos, 0);
  EXPECT_EQ(entry.value_size, 0);
  EXPECT_EQ(entry.timestamp, 0);
}

TEST(KeyDirEntry, ParameterizedConstructor) {
  KeyDirEntry entry(42, "/test/path.data", 100, 200, 9999999999);
  EXPECT_EQ(entry.file_id, 42);
  EXPECT_EQ(entry.file_path, "/test/path.data");
  EXPECT_EQ(entry.value_pos, 100);
  EXPECT_EQ(entry.value_size, 200);
  EXPECT_EQ(entry.timestamp, 9999999999);
}

}  // namespace
