//
// Created by Copilot on 15/11/25.
//

#ifndef KEYDIR_H
#define KEYDIR_H

#include <optional>
#include <string>

#include "KeyDirEntry.h"
#include "src/lru_cache/HashMap.h"

/**
 * KeyDir - In-memory index for Bitcask-style key-value store
 * 
 * This class maintains an in-memory hash table that maps keys to their
 * metadata (file location, position, size, timestamp). It provides O(1)
 * lookups for fast key access.
 */
class KeyDir {
 private:
    HashMap<std::string, KeyDirEntry> hash_map;
    size_t size_ = 0;
 public:
  KeyDir() = default;

  // Put or update a key in the KeyDir
  // TODO: Implement this method to insert or update an entry
  // - Store the entry in the data structure using the key
  // - If key already exists, it should be overwritten (last-write-wins)
  void put(const std::string& key, const KeyDirEntry& entry) {
    // TODO: Implement me
    if (this->hash_map.has(key)) {
      this-> hash_map.put(key, entry);
    }else {
      this->hash_map.put(key, entry);
      ++this->size_ ;
    }

  }


  std::optional<KeyDirEntry> get(const std::string& key) {
    if (this->hash_map.has(key)) {
      return this->hash_map.get(key);
    }
    return std::nullopt;
  }

  // Remove a key from the KeyDir
  // TODO: Implement this method to delete a key from the index
  // - Remove the key-value pair from the data structure
  // - Should handle non-existent keys gracefully (no error)
  void remove(const std::string& key) {
    // TODO: Implement me
    if (this->hash_map.has(key)) {
      this->hash_map.remove(key);
      --this->size_;
    }

  }

  // Check if a key exists in the KeyDir
  // TODO: Implement this method to check key existence
  // - Return true if key exists, false otherwise
  // - Do not modify the data structure (const method)
  bool has(const std::string& key) {
    // TODO: Implement me
    return this->hash_map.has(key);
  }

  // Get the number of entries
  // TODO: Implement this method to return the number of keys stored
  // - Return the count of key-value pairs in the data structure
  std::size_t size() const  {
    // TODO: Implement me
    return this->size_;
  }

  // Clear all entries
  // TODO: Implement this method to remove all keys from the index
  // - Clear the entire data structure
  // - After calling this, size() should return 0
  void clear() {
    this->hash_map.clear();
    this->size_ = 0;
  }

  ~KeyDir() = default;
};

#endif  // KEYDIR_H
