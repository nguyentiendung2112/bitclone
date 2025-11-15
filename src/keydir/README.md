# KeyDir Implementation Exercise

This directory contains skeleton code for implementing a Bitcask-style KeyDir (in-memory index).

## What is KeyDir?

KeyDir is an in-memory hash table that maps keys to metadata about where their values are stored on disk. It's a core component of the Bitcask storage architecture, enabling O(1) lookups for keys.

## Files

- **KeyDirEntry.h**: Metadata structure holding information about where a value is stored
- **KeyDir.h**: The main KeyDir class providing the in-memory index
- **tests/cpp/keydir/test_keydir.cc**: Test cases to verify your implementation

## What You Need to Implement

### 1. KeyDirEntry Constructor (KeyDirEntry.h)

Complete the initialization list in the parameterized constructor:

```cpp
KeyDirEntry(std::uint64_t file_id, std::string file_path,
            std::uint64_t value_pos, std::uint64_t value_size,
            std::uint64_t timestamp)
    : file_id(?),           // Initialize with parameter
      file_path(?),         // Use std::move() to avoid copying
      value_pos(?),         // Initialize with parameter
      value_size(?),        // Initialize with parameter
      timestamp(?) {}       // Initialize with parameter
```

### 2. KeyDir Methods (KeyDir.h)

The `entries` member variable is already declared for you. Implement these methods:

#### `put(key, entry)`
- Store or update an entry in the hash map
- Use `entries[key] = entry`

#### `get(key)`
- Return `std::optional<KeyDirEntry>`
- Find the key in the map
- If found, return the entry wrapped in `std::optional`
- If not found, return `std::nullopt`

#### `remove(key)`
- Remove a key from the map
- Use `entries.erase(key)`

#### `has(key)`
- Check if a key exists
- Return `entries.find(key) != entries.end()`

#### `size()`
- Return the number of entries
- Use `entries.size()`

#### `clear()`
- Remove all entries
- Use `entries.clear()`

### 3. Tests (tests/cpp/keydir/test_keydir.cc)

Uncomment and complete the test implementations. Each test has:
- Comments explaining what to test
- Example code showing the pattern
- Assertions to verify behavior

## Building and Testing

```bash
# Build and run tests with Bazel
bazel test //...:test-keydir

# Or compile manually with g++
g++ -std=c++17 -I. tests/cpp/keydir/test_keydir.cc -lgtest -lgtest_main -pthread
```

## Expected Behavior

- **O(1) lookups**: Using std::unordered_map provides average O(1) performance
- **Last-write-wins**: Updating an existing key overwrites the old entry
- **Safe lookups**: `get()` returns `std::optional` to handle missing keys gracefully
- **No crashes**: Operations on non-existent keys should not crash

## Tips

1. Start with the constructor in KeyDirEntry.h
2. Then implement KeyDir methods one at a time
3. Implement and run tests after each method to verify correctness
4. Pay attention to const correctness (methods that don't modify state should be const)
5. Use `std::move()` for file_path to avoid unnecessary string copying

## Resources

- [Bitcask paper](https://riak.com/assets/bitcask-intro.pdf)
- [std::unordered_map reference](https://en.cppreference.com/w/cpp/container/unordered_map)
- [std::optional reference](https://en.cppreference.com/w/cpp/utility/optional)

Good luck with your implementation!
