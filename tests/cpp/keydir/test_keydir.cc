//
// Created by Copilot on 15/11/25.
//
#include "gtest/gtest.h"
#include "src/keydir/KeyDir.h"
#include "src/keydir/KeyDirEntry.h"

namespace {

// Test: Put a key and retrieve it
// TODO: Implement this test
// - Create a KeyDir instance
// - Create a KeyDirEntry with test data
// - Put the entry into the KeyDir with a key
// - Get the entry back using the same key
// - Verify all fields match the original entry
TEST(KeyDir, PutAndGet) {
  // TODO: Implement test
  // KeyDir keydir;
  // KeyDirEntry entry(1, "/path/to/file1.data", 0, 100, 1234567890);
  // keydir.put("key1", entry);
  // auto result = keydir.get("key1");
  // ASSERT_TRUE(result.has_value());
  // EXPECT_EQ(result->file_id, 1);
  // ... verify other fields
}

// Test: Get a non-existent key should return empty optional
// TODO: Implement this test
// - Create a KeyDir instance
// - Try to get a key that was never added
// - Verify that get() returns std::nullopt (result.has_value() is false)
TEST(KeyDir, GetNonExistentKey) {
  // TODO: Implement test
  // KeyDir keydir;
  // auto result = keydir.get("nonexistent");
  // EXPECT_FALSE(result.has_value());
}

// Test: Update an existing key (last-write-wins)
// TODO: Implement this test
// - Create a KeyDir instance
// - Put a key with initial entry data
// - Put the same key again with different entry data
// - Verify that get() returns the most recent entry
// - The size should remain the same (1 key, not 2)
TEST(KeyDir, UpdateExistingKey) {
  // TODO: Implement test
  // KeyDir keydir;
  // KeyDirEntry entry1(1, "/path/to/file1.data", 0, 100, 1234567890);
  // KeyDirEntry entry2(2, "/path/to/file2.data", 200, 150, 1234567900);
  // keydir.put("key1", entry1);
  // keydir.put("key1", entry2);
  // auto result = keydir.get("key1");
  // ASSERT_TRUE(result.has_value());
  // EXPECT_EQ(result->file_id, 2);  // Should be the second entry
  // ... verify other fields from entry2
}

// Test: Check if keys exist using has()
// TODO: Implement this test
// - Verify has() returns false for non-existent key
// - Add a key
// - Verify has() returns true for the added key
// - Verify has() returns false for a different key
TEST(KeyDir, Has) {
  // TODO: Implement test
  // KeyDir keydir;
  // KeyDirEntry entry(1, "/path/to/file1.data", 0, 100, 1234567890);
  // EXPECT_FALSE(keydir.has("key1"));
  // keydir.put("key1", entry);
  // EXPECT_TRUE(keydir.has("key1"));
  // EXPECT_FALSE(keydir.has("key2"));
}

// Test: Remove a key from KeyDir
// TODO: Implement this test
// - Add a key to the KeyDir
// - Verify the key exists
// - Remove the key
// - Verify the key no longer exists (has() returns false)
// - Verify get() returns std::nullopt for the removed key
TEST(KeyDir, Remove) {
  // TODO: Implement test
  // KeyDir keydir;
  // KeyDirEntry entry(1, "/path/to/file1.data", 0, 100, 1234567890);
  // keydir.put("key1", entry);
  // EXPECT_TRUE(keydir.has("key1"));
  // keydir.remove("key1");
  // EXPECT_FALSE(keydir.has("key1"));
  // auto result = keydir.get("key1");
  // EXPECT_FALSE(result.has_value());
}

// Test: Remove a non-existent key should not crash
// TODO: Implement this test
// - Try to remove a key that doesn't exist
// - This should complete without errors/crashes
// - Verify the key still doesn't exist after remove
TEST(KeyDir, RemoveNonExistentKey) {
  // TODO: Implement test
  // KeyDir keydir;
  // keydir.remove("nonexistent");  // Should not crash
  // EXPECT_FALSE(keydir.has("nonexistent"));
}

// Test: Track the size (number of keys) in KeyDir
// TODO: Implement this test
// - Verify size is 0 initially
// - Add keys and verify size increases
// - Update an existing key and verify size stays the same
// - Remove a key and verify size decreases
TEST(KeyDir, Size) {
  // TODO: Implement test
  // KeyDir keydir;
  // EXPECT_EQ(keydir.size(), 0);
  // KeyDirEntry entry1(1, "/path/to/file1.data", 0, 100, 1234567890);
  // keydir.put("key1", entry1);
  // EXPECT_EQ(keydir.size(), 1);
  // keydir.put("key2", entry1);
  // EXPECT_EQ(keydir.size(), 2);
  // keydir.put("key1", entry1);  // update doesn't increase size
  // EXPECT_EQ(keydir.size(), 2);
  // keydir.remove("key1");
  // EXPECT_EQ(keydir.size(), 1);
}

// Test: Clear all entries from KeyDir
// TODO: Implement this test
// - Add multiple keys to the KeyDir
// - Verify size is greater than 0
// - Call clear()
// - Verify size is 0
// - Verify all previously added keys no longer exist
TEST(KeyDir, Clear) {
  // TODO: Implement test
  // KeyDir keydir;
  // KeyDirEntry entry1(1, "/path/to/file1.data", 0, 100, 1234567890);
  // KeyDirEntry entry2(2, "/path/to/file2.data", 100, 200, 1234567900);
  // keydir.put("key1", entry1);
  // keydir.put("key2", entry2);
  // EXPECT_EQ(keydir.size(), 2);
  // keydir.clear();
  // EXPECT_EQ(keydir.size(), 0);
  // EXPECT_FALSE(keydir.has("key1"));
  // EXPECT_FALSE(keydir.has("key2"));
}

// Test: Handle multiple keys efficiently
// TODO: Implement this test
// - Add many keys (e.g., 100) in a loop
// - Verify size is correct
// - Retrieve all keys and verify their data is correct
// This tests scalability and ensures no data corruption with many entries
TEST(KeyDir, MultipleKeys) {
  // TODO: Implement test
  // KeyDir keydir;
  // for (int i = 0; i < 100; ++i) {
  //   std::string key = "key" + std::to_string(i);
  //   KeyDirEntry entry(i, "/path/to/file" + std::to_string(i) + ".data",
  //                     i * 100, 100, 1234567890 + i);
  //   keydir.put(key, entry);
  // }
  // EXPECT_EQ(keydir.size(), 100);
  // for (int i = 0; i < 100; ++i) {
  //   std::string key = "key" + std::to_string(i);
  //   EXPECT_TRUE(keydir.has(key));
  //   auto result = keydir.get(key);
  //   ASSERT_TRUE(result.has_value());
  //   EXPECT_EQ(result->file_id, i);
  //   EXPECT_EQ(result->value_pos, i * 100);
  // }
}

// Test: Handle empty string as a key
// TODO: Implement this test
// - Empty string should be a valid key
// - Put an entry with empty string key
// - Verify it can be retrieved
TEST(KeyDir, EmptyStringKey) {
  // TODO: Implement test
  // KeyDir keydir;
  // KeyDirEntry entry(1, "/path/to/file1.data", 0, 100, 1234567890);
  // keydir.put("", entry);
  // EXPECT_TRUE(keydir.has(""));
  // auto result = keydir.get("");
  // ASSERT_TRUE(result.has_value());
  // EXPECT_EQ(result->file_id, 1);
}

// Test: Handle very long keys
// TODO: Implement this test
// - Create a long key (e.g., 1000 characters)
// - Put and retrieve entry with long key
// - Verify it works correctly (no truncation or corruption)
TEST(KeyDir, LongKey) {
  // TODO: Implement test
  // KeyDir keydir;
  // std::string long_key(1000, 'a');
  // KeyDirEntry entry(1, "/path/to/file1.data", 0, 100, 1234567890);
  // keydir.put(long_key, entry);
  // EXPECT_TRUE(keydir.has(long_key));
  // auto result = keydir.get(long_key);
  // ASSERT_TRUE(result.has_value());
  // EXPECT_EQ(result->file_id, 1);
}

// Test: KeyDirEntry default constructor
// TODO: Implement this test
// - Create a KeyDirEntry using default constructor
// - Verify all fields are initialized to 0 or empty
TEST(KeyDirEntry, DefaultConstructor) {
  // TODO: Implement test
  // KeyDirEntry entry;
  // EXPECT_EQ(entry.file_id, 0);
  // EXPECT_EQ(entry.value_pos, 0);
  // EXPECT_EQ(entry.value_size, 0);
  // EXPECT_EQ(entry.timestamp, 0);
}

// Test: KeyDirEntry parameterized constructor
// TODO: Implement this test
// - Create a KeyDirEntry with specific values
// - Verify all fields are set correctly
TEST(KeyDirEntry, ParameterizedConstructor) {
  // TODO: Implement test
  // KeyDirEntry entry(42, "/test/path.data", 100, 200, 9999999999);
  // EXPECT_EQ(entry.file_id, 42);
  // EXPECT_EQ(entry.file_path, "/test/path.data");
  // EXPECT_EQ(entry.value_pos, 100);
  // EXPECT_EQ(entry.value_size, 200);
  // EXPECT_EQ(entry.timestamp, 9999999999);
}

}  // namespace
