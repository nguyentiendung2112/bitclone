# Put/Get Operations Design for Bitcask Key-Value Store

## Overview
This document outlines the design for implementing efficient `put` and `get` operations for a Bitcask-style key-value store. The implementation leverages the existing KeyDir (in-memory index) for O(1) lookups and the file handler components for disk I/O operations.

## Design Checklist

### 1. Core Components

#### 1.1 BitcaskStore Class
- [ ] Create main `BitcaskStore` class to coordinate all operations
- [ ] Maintain reference to KeyDir for in-memory indexing
- [ ] Track active data file descriptor and file metadata
- [ ] Manage file rotation based on size threshold
- [ ] Handle initialization and cleanup of resources

#### 1.2 Data File Management
- [ ] Implement active file tracking (file descriptor, file path, current size)
- [ ] Track file ID generation (monotonically increasing)
- [ ] Implement file rotation logic when size exceeds threshold
- [ ] Ensure proper file naming convention (zero-padded IDs)
- [ ] Handle file opening/closing and descriptor management

#### 1.3 Configuration
- [ ] Define maximum file size for rotation (e.g., 256MB default)
- [ ] Configure fsync strategy (per-write, batch, or on-rotation)
- [ ] Set base directory path for data files
- [ ] Define file naming pattern

### 2. Put Operation Design

#### 2.1 Put Method Interface
- [ ] `bool put(const std::string& key, const std::byte* value, size_t value_size)`
- [ ] Return success/failure status
- [ ] Handle null/empty keys appropriately
- [ ] Support null value pointer with zero size (for tombstones)

#### 2.2 Put Implementation Steps
- [ ] Validate input parameters (key, value pointer, size)
- [ ] Get current file position before write
- [ ] Get current timestamp
- [ ] Serialize record using LogWriter
- [ ] Append serialized data to active file
- [ ] Calculate new file position after write
- [ ] Create KeyDirEntry with metadata
- [ ] Update KeyDir with new entry
- [ ] Check if file rotation is needed
- [ ] Perform rotation if threshold exceeded
- [ ] Optional: fsync based on configuration

#### 2.3 Overwrite Handling
- [ ] Check if key exists in KeyDir before put
- [ ] Allow last-write-wins semantics
- [ ] Update KeyDir entry atomically
- [ ] Previous version remains on disk (space reclaimed during compaction)

#### 2.4 Error Handling
- [ ] Handle file write failures
- [ ] Handle file descriptor errors
- [ ] Handle KeyDir update failures
- [ ] Ensure atomicity: if write fails, don't update KeyDir
- [ ] Log errors for debugging

### 3. Get Operation Design

#### 3.1 Get Method Interface
- [ ] `std::optional<std::vector<std::byte>> get(const std::string& key)`
- [ ] Return optional containing value or nullopt if not found
- [ ] Const method (doesn't modify store state)

#### 3.2 Get Implementation Steps
- [ ] Lookup key in KeyDir
- [ ] Return nullopt if key not found
- [ ] Extract metadata from KeyDirEntry (file_id, file_path, value_pos, value_size)
- [ ] Open file descriptor for the data file (cache if needed)
- [ ] Use LogReader to read record at specified position
- [ ] Validate record integrity
- [ ] Extract and return value from record
- [ ] Handle file descriptor cleanup

#### 3.3 File Descriptor Management
- [ ] Option 1: Open file on each read (simple, but slower)
- [ ] Option 2: Cache file descriptors (better performance)
- [ ] Implement FD cache with LRU eviction
- [ ] Handle max open files limit
- [ ] Ensure thread-safe access if needed

#### 3.4 Error Handling
- [ ] Handle file not found errors
- [ ] Handle file read failures
- [ ] Handle corrupted data (CRC mismatch)
- [ ] Handle unexpected file size/truncation
- [ ] Return nullopt on errors (fail gracefully)

### 4. Delete Operation Design

#### 4.1 Delete Method Interface
- [ ] `bool del(const std::string& key)`
- [ ] Return true if key existed, false otherwise

#### 4.2 Delete Implementation Steps
- [ ] Check if key exists in KeyDir
- [ ] Write tombstone record (value_size = 0)
- [ ] Remove key from KeyDir immediately
- [ ] Tombstone remains on disk for compaction
- [ ] Optional: fsync based on configuration

#### 4.3 Tombstone Format
- [ ] Use existing LogWriter with null value pointer and zero size
- [ ] Record format: [key_size][value_size=0][key]
- [ ] Timestamp marks deletion time

### 5. File Rotation

#### 5.1 Rotation Triggers
- [ ] Check file size after each put operation
- [ ] Rotate when current file size >= max_file_size
- [ ] Can also trigger on close/shutdown

#### 5.2 Rotation Process
- [ ] Fsync current active file
- [ ] Close current active file descriptor
- [ ] Increment file ID counter
- [ ] Generate new file path with new ID
- [ ] Open new file descriptor (create if doesn't exist)
- [ ] Update active file metadata
- [ ] Reset current file size counter

#### 5.3 Rotation Atomicity
- [ ] Ensure rotation happens atomically
- [ ] No writes should be lost during rotation
- [ ] KeyDir updates continue referencing correct files

### 6. Synchronization and Thread Safety

#### 6.1 Single-Writer Model
- [ ] Enforce single writer at a time
- [ ] Use mutex/lock for put operations
- [ ] Use mutex/lock for delete operations
- [ ] Use mutex/lock for file rotation

#### 6.2 Multi-Reader Support
- [ ] Get operations can be concurrent (read-only)
- [ ] Use shared lock for KeyDir reads
- [ ] File descriptors can be shared (OS handles this)
- [ ] Consider reader-writer lock for KeyDir

#### 6.3 Lock Granularity
- [ ] Option 1: Single mutex for entire BitcaskStore
- [ ] Option 2: Separate locks for KeyDir and file operations
- [ ] Option 3: Fine-grained locking per file
- [ ] Start with Option 1 for simplicity

### 7. Startup and Recovery

#### 7.1 Initialization
- [ ] Create/open database directory
- [ ] Scan for existing data files
- [ ] Determine last file ID used
- [ ] Build KeyDir by scanning all files
- [ ] Use LogReader to read each record
- [ ] Update KeyDir with latest version of each key
- [ ] Handle tombstones during rebuild

#### 7.2 KeyDir Rebuild Process
- [ ] Iterate through data files in ascending order
- [ ] For each file, scan records sequentially
- [ ] Extract key and metadata from each record
- [ ] Update KeyDir (last write wins)
- [ ] Skip/remove tombstones from KeyDir
- [ ] Track total keys and data size

#### 7.3 Crash Recovery
- [ ] Handle truncated files gracefully
- [ ] Stop scanning at first corrupted record
- [ ] Ignore trailing partial records
- [ ] CRC validation ensures data integrity
- [ ] KeyDir reflects all valid records

### 8. Performance Optimizations

#### 8.1 Write Path Optimizations
- [ ] Batch fsync instead of per-write
- [ ] Pre-allocate file space to reduce fragmentation
- [ ] Use direct I/O if appropriate
- [ ] Buffer writes in memory before flushing

#### 8.2 Read Path Optimizations
- [ ] Cache file descriptors (LRU cache)
- [ ] Use mmap for frequently accessed files
- [ ] Read-ahead for sequential access
- [ ] Cache recently read values (optional)

#### 8.3 Memory Optimizations
- [ ] Use string_view where possible
- [ ] Minimize KeyDir memory footprint
- [ ] Consider key interning for duplicate keys
- [ ] Use arena allocator for temporary buffers

### 9. Testing Requirements

#### 9.1 Unit Tests
- [ ] Test put operation with various key/value sizes
- [ ] Test get operation for existing and non-existing keys
- [ ] Test delete operation and tombstone handling
- [ ] Test overwrite semantics (last-write-wins)
- [ ] Test empty key and empty value handling
- [ ] Test large keys and large values
- [ ] Test file rotation logic
- [ ] Test KeyDir synchronization

#### 9.2 Integration Tests
- [ ] Test put followed by get (round-trip)
- [ ] Test multiple puts and gets
- [ ] Test puts across file rotation boundary
- [ ] Test delete followed by get (should return nullopt)
- [ ] Test startup recovery from existing files
- [ ] Test concurrent reads (if multi-threaded)

#### 9.3 Stress Tests
- [ ] Test with millions of keys
- [ ] Test with large values (>1MB)
- [ ] Test rapid put/get cycles
- [ ] Test file rotation under load
- [ ] Memory usage monitoring
- [ ] Performance benchmarking

#### 9.4 Error Handling Tests
- [ ] Test disk full scenario
- [ ] Test corrupted file handling
- [ ] Test invalid input handling
- [ ] Test recovery from partial writes
- [ ] Test cleanup on errors

### 10. Implementation Files

#### 10.1 New Header Files
- [ ] `src/bitcask/BitcaskStore.h` - Main store class
- [ ] `src/bitcask/BitcaskConfig.h` - Configuration structure
- [ ] `src/bitcask/FileMetadata.h` - Active file tracking

#### 10.2 New Test Files
- [ ] `tests/cpp/bitcask/test_bitcask_store.cc` - Main functionality tests
- [ ] `tests/cpp/bitcask/test_put_operation.cc` - Put operation tests
- [ ] `tests/cpp/bitcask/test_get_operation.cc` - Get operation tests
- [ ] `tests/cpp/bitcask/test_delete_operation.cc` - Delete operation tests
- [ ] `tests/cpp/bitcask/test_file_rotation.cc` - File rotation tests
- [ ] `tests/cpp/bitcask/test_recovery.cc` - Startup recovery tests

#### 10.3 Build Configuration
- [ ] Update BUILD file with new targets
- [ ] Add bitcask library target
- [ ] Add test targets for new tests
- [ ] Define dependencies

### 11. API Design Summary

```cpp
class BitcaskStore {
public:
    // Constructor: opens/creates database at given directory
    BitcaskStore(const std::string& directory, const BitcaskConfig& config);
    
    // Put a key-value pair
    bool put(const std::string& key, const std::byte* value, size_t value_size);
    
    // Get value for a key
    std::optional<std::vector<std::byte>> get(const std::string& key) const;
    
    // Delete a key
    bool del(const std::string& key);
    
    // Sync all changes to disk
    bool sync();
    
    // Get statistics
    StoreStats getStats() const;
    
    // Destructor: cleanup resources
    ~BitcaskStore();
};
```

### 12. Data Structures

#### 12.1 FileMetadata
```cpp
struct FileMetadata {
    uint64_t file_id;
    std::string file_path;
    int file_descriptor;
    uint64_t current_size;
};
```

#### 12.2 BitcaskConfig
```cpp
struct BitcaskConfig {
    uint64_t max_file_size = 256 * 1024 * 1024;  // 256MB
    bool fsync_each_write = false;
    size_t fd_cache_size = 100;
    std::string file_extension = ".data";
};
```

#### 12.3 StoreStats
```cpp
struct StoreStats {
    size_t total_keys;
    size_t total_files;
    uint64_t total_size;
    uint64_t active_file_size;
};
```

### 13. Error Handling Strategy

#### 13.1 Error Types
- [ ] Define custom exception types or error codes
- [ ] FileIOException - for file operation failures
- [ ] CorruptDataException - for data integrity errors
- [ ] InvalidArgumentException - for invalid inputs
- [ ] OutOfSpaceException - for disk space issues

#### 13.2 Error Propagation
- [ ] Use exceptions for unrecoverable errors
- [ ] Use return values (bool, optional) for expected failures
- [ ] Log all errors for debugging
- [ ] Provide detailed error messages

### 14. Documentation

#### 14.1 Code Documentation
- [ ] Document all public APIs
- [ ] Document configuration options
- [ ] Document thread-safety guarantees
- [ ] Document performance characteristics

#### 14.2 User Documentation
- [ ] Create README for bitcask component
- [ ] Document usage examples
- [ ] Document performance tuning guidelines
- [ ] Document recovery procedures

### 15. Future Enhancements (Not in Current Scope)

- [ ] Hint files for faster startup
- [ ] Background compaction
- [ ] Compression support
- [ ] Encryption support
- [ ] Multi-process support with lock file
- [ ] TTL/expiration
- [ ] Iteration API
- [ ] Batch write API
- [ ] Snapshot API

## Implementation Priority

1. **Phase 1: Core Functionality**
   - BitcaskStore class skeleton
   - Basic put operation (single file)
   - Basic get operation
   - KeyDir integration
   - Basic unit tests

2. **Phase 2: File Management**
   - File rotation
   - Delete operation (tombstones)
   - File descriptor caching
   - Integration tests

3. **Phase 3: Recovery**
   - Startup recovery
   - KeyDir rebuild from files
   - Crash recovery tests

4. **Phase 4: Optimization**
   - Performance tuning
   - Batch operations
   - Memory optimizations
   - Stress testing

5. **Phase 5: Production Readiness**
   - Error handling refinement
   - Documentation completion
   - Performance benchmarking
   - Code review and cleanup

## Success Criteria

- [ ] All put operations are durable (configurable fsync)
- [ ] All get operations use KeyDir for O(1) lookup
- [ ] Overwrites work correctly (last-write-wins)
- [ ] Deletes create tombstones
- [ ] File rotation works without data loss
- [ ] Startup recovery rebuilds KeyDir correctly
- [ ] All unit tests pass
- [ ] Performance meets requirements (>10k ops/sec)
- [ ] Memory usage is reasonable (<100 bytes/key overhead)
- [ ] Code is clean and well-documented

## Performance Targets

- **Write throughput**: > 10,000 puts/second
- **Read latency**: < 1ms for cached files, < 10ms for uncached
- **Memory overhead**: < 100 bytes per key in KeyDir
- **Startup time**: < 1 second per 100MB of data
- **File rotation overhead**: < 10ms

## Notes

- This design focuses on correctness first, optimization second
- Single-writer model simplifies implementation
- File format is compatible with existing LogReader/LogWriter
- KeyDir provides O(1) lookups as required
- Design allows for future enhancements without breaking changes
