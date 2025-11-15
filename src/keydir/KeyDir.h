//
// Created by Copilot on 15/11/25.
//

#ifndef KEYDIR_H
#define KEYDIR_H

#include <string>
#include <unordered_map>
#include <optional>
#include "KeyDirEntry.h"

class KeyDir {
 private:
  std::unordered_map<std::string, KeyDirEntry> entries;

 public:
  KeyDir() = default;

  // Put or update a key in the KeyDir
  void put(const std::string& key, const KeyDirEntry& entry) {
    entries[key] = entry;
  }

  // Get an entry from the KeyDir
  std::optional<KeyDirEntry> get(const std::string& key) const {
    auto it = entries.find(key);
    if (it != entries.end()) {
      return it->second;
    }
    return std::nullopt;
  }

  // Remove a key from the KeyDir
  void remove(const std::string& key) {
    entries.erase(key);
  }

  // Check if a key exists in the KeyDir
  bool has(const std::string& key) const {
    return entries.find(key) != entries.end();
  }

  // Get the number of entries
  std::size_t size() const {
    return entries.size();
  }

  // Clear all entries
  void clear() {
    entries.clear();
  }

  ~KeyDir() = default;
};

#endif  // KEYDIR_H
