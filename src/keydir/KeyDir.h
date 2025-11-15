//
// Created by Copilot on 15/11/25.
//

#ifndef KEYDIR_H
#define KEYDIR_H

#include <optional>
#include <string>
#include <unordered_map>

#include "KeyDirEntry.h"

/**
 * KeyDir - In-memory index for Bitcask-style key-value store
 * 
 * This class maintains an in-memory hash table that maps keys to their
 * metadata (file location, position, size, timestamp). It provides O(1)
 * lookups for fast key access.
 */
class KeyDir {
 private:
  // TODO: Declare a data structure to store key-value mappings
  // Hint: Use std::unordered_map<std::string, KeyDirEntry>
  std::unordered_map<std::string, KeyDirEntry> entries;

 public:
  KeyDir() = default;

  // Put or update a key in the KeyDir
  // TODO: Implement this method to insert or update an entry
  // - Store the entry in the data structure using the key
  // - If key already exists, it should be overwritten (last-write-wins)
  void put(const std::string& key, const KeyDirEntry& entry) {
    // TODO: Implement me
  }

  // Get an entry from the KeyDir
  // TODO: Implement this method to retrieve an entry by key
  // - Return std::optional<KeyDirEntry> to handle key-not-found cases
  // - If key exists, return the entry wrapped in std::optional
  // - If key doesn't exist, return std::nullopt
  std::optional<KeyDirEntry> get(const std::string& key) const {
    // TODO: Implement me
    return std::nullopt;
  }

  // Remove a key from the KeyDir
  // TODO: Implement this method to delete a key from the index
  // - Remove the key-value pair from the data structure
  // - Should handle non-existent keys gracefully (no error)
  void remove(const std::string& key) {
    // TODO: Implement me
  }

  // Check if a key exists in the KeyDir
  // TODO: Implement this method to check key existence
  // - Return true if key exists, false otherwise
  // - Do not modify the data structure (const method)
  bool has(const std::string& key) const {
    // TODO: Implement me
    return false;
  }

  // Get the number of entries
  // TODO: Implement this method to return the number of keys stored
  // - Return the count of key-value pairs in the data structure
  std::size_t size() const {
    // TODO: Implement me
    return 0;
  }

  // Clear all entries
  // TODO: Implement this method to remove all keys from the index
  // - Clear the entire data structure
  // - After calling this, size() should return 0
  void clear() {
    // TODO: Implement me
  }

  ~KeyDir() = default;
};

#endif  // KEYDIR_H
