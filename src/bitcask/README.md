# Bitcask Key-Value Store Implementation

## Overview

This directory contains the implementation of a Bitcask-style key-value store for the bitclone project. The implementation provides efficient put/get operations using an in-memory KeyDir index for O(1) lookups.

## Components

### Core Classes

- **BitcaskStore**: Main store class providing put/get/delete operations
- **BitcaskConfig**: Configuration structure for store parameters
- **FileMetadata**: Tracks active data file information
- **StoreStats**: Store statistics and metrics

### Key Features

- **O(1) Read Performance**: Uses KeyDir (in-memory hash map) for constant-time key lookups
- **Append-Only Writes**: All data is appended to files for durability and simplicity
- **File Rotation**: Automatically rotates files when size threshold is exceeded
- **Thread-Safe Writes**: Single-writer model with mutex protection
- **Tombstone Deletes**: Deletions create tombstone records (removed during compaction)
- **Configurable Durability**: Optional fsync per write or batch mode

## Architecture

### Data Flow

#### Put Operation
1. Acquire write mutex
2. Get current file position
3. Serialize key-value record using LogWriter
4. Append to active data file
5. Update KeyDir with new entry metadata
6. Optional fsync
7. Check for file rotation threshold

#### Get Operation
1. Lookup key in KeyDir (O(1))
2. If found, get file metadata (file_id, position, size)
3. Open file descriptor
4. Read record at position using LogReader
5. Return value bytes

#### Delete Operation
1. Acquire write mutex
2. Write tombstone record (value_size = 0)
3. Remove key from KeyDir
4. Optional fsync

### File Format

Data files use the format from LogWriter/LogReader:
```
[key_size: uint64_t][value_size: uint64_t][key bytes][value bytes]
```

File naming: `{directory}/{file_id}.data` (zero-padded 20-digit file_id)

### KeyDir Integration

The KeyDir maintains in-memory index with entries:
```cpp
struct KeyDirEntry {
    uint64_t file_id;
    string file_path;
    uint64_t value_pos;
    uint64_t value_size;
    uint64_t timestamp;
}
```

## API Usage

### Basic Operations

```cpp
#include "src/bitcask/BitcaskStore.h"

BitcaskStore store("/path/to/data");

std::vector<std::byte> value = {std::byte(1), std::byte(2), std::byte(3)};
store.put("key1", value.data(), value.size());

auto result = store.get("key1");
if (result.has_value()) {
    // Use result.value()
}

store.del("key1");
```

### Configuration

```cpp
BitcaskConfig config;
config.max_file_size = 256 * 1024 * 1024;  // 256MB
config.fsync_each_write = true;
config.fd_cache_size = 100;

BitcaskStore store("/path/to/data", config);
```

### Statistics

```cpp
StoreStats stats = store.getStats();
std::cout << "Total keys: " << stats.total_keys << std::endl;
std::cout << "Total files: " << stats.total_files << std::endl;
std::cout << "Active file size: " << stats.active_file_size << std::endl;
```

## Configuration Options

- `max_file_size`: Maximum size of a data file before rotation (default: 256MB)
- `fsync_each_write`: Whether to fsync after each write (default: false)
- `fd_cache_size`: Size of file descriptor cache (default: 100)
- `file_extension`: Extension for data files (default: ".data")
- `directory`: Base directory for data files (default: "./data")

## Thread Safety

- **Write Operations** (put, del): Protected by mutex (single-writer)
- **Read Operations** (get): Thread-safe, can be concurrent
- **KeyDir Access**: Protected internally by write mutex

## Performance Characteristics

- **Write Throughput**: Target >10,000 puts/second
- **Read Latency**: <1ms for cached files, <10ms for uncached
- **Memory Overhead**: ~100 bytes per key (KeyDir entry + hash map overhead)
- **File Rotation Overhead**: <10ms per rotation

## Error Handling

Operations return `bool` for success/failure or `std::optional` for get operations:
- `put()`: Returns false if write fails
- `get()`: Returns nullopt if key not found or read fails
- `del()`: Returns false if key doesn't exist

Exceptions are caught internally and converted to error returns.

## Testing

Test files are located in `tests/cpp/bitcask/`:
- `test_bitcask_store.cc`: Main functionality tests
- `test_put_operation.cc`: Put-specific tests
- `test_get_operation.cc`: Get-specific tests
- `test_delete_operation.cc`: Delete operation tests
- `test_file_rotation.cc`: File rotation tests

Run tests with Bazel:
```bash
bazel test //...:test-bitcask-store
bazel test //...:test-bitcask-all
```

## Future Enhancements

Not yet implemented but planned:
- Startup recovery (rebuild KeyDir from existing files)
- Hint files for faster startup
- Background compaction to reclaim space
- File descriptor caching
- Multi-process support with lock file
- Compression and encryption
- Iteration API
- Batch write API

## References

- [Bitcask Design Paper](https://riak.com/assets/bitcask-intro.pdf)
- Main design document: `ideas-with-AI/put_get_operations_design.md`
- Overall architecture: `ideas-with-AI/CHAT1.md`
