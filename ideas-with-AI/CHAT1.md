# Bitcask-style KV Store (C++) — Concept and Design

This document outlines a pragmatic design for a Bitcask-inspired key-value store implemented in C++. It focuses on append-only data files, an in-memory index for O(1) reads, and straightforward compaction.

## Goals and Assumptions

- Simple, robust key-value store optimized for SSDs.
- Append-only storage with fast recovery via replay and checksums.
- O(1) reads using an in-memory KeyDir: `key -> (file_id, value_pos, value_size, timestamp)`.
- Single-writer, multi-reader model.
- Start with a minimal implementation; add hint files, background compaction, and more later.

---

## On-Disk Data Model

### Data files
- Naming: monotonically increasing IDs with zero-padded names, e.g., `00000000000000000001.data`.
- Records are appended in little-endian format:
    - `crc32` (4 bytes): checksum of the rest of the record.
    - `timestamp` (8 bytes): Unix seconds (ns optional later).
    - `key_size` (4 bytes)
    - `value_size` (4 bytes)
    - `key` (key_size bytes)
    - `value` (value_size bytes; 0 bytes means tombstone).
- CRC coverage: bytes from `timestamp` through `value` (excludes the `crc32` field).
- Recovery rule: while scanning a file, stop at the first corrupt or truncated record (assumed trailing garbage after a crash).

Notes for future extensions:
- Optional `record_length` to accelerate scanning.
- Optional `version` byte for format evolution.

### Tombstones
- A delete writes a record with `value_size = 0`.
- Compaction must respect delete semantics: drop tombstones only once older versions are guaranteed not to survive in remaining segments.

### File rotation
- One active file receives appends.
- Rotate when size exceeds `max_file_size`.
- Rotated files are immutable “segments.”

### Hint files (later)
- Per-segment `.hint` files: `(key, file_id, value_pos, value_size, timestamp)`.
- Startup rebuild prefers hints; falls back to scanning `.data` if missing/corrupt.

### Locking / Manifests (optional later)
- Lock file to enforce single writer per DB directory.
- MANIFEST to make segment set explicit and help recover/finish interrupted compactions.

---

## In-Memory KeyDir

- Entry fields:
    - `file_id` (u64)
    - `file_path` or an index into a vector of file metadata
    - `value_pos` (u64)
    - `value_size` (u32 or u64)
    - `timestamp` (u64)
- Memory footprint considerations:
    - Hash map node overhead + key string dominates.
    - 10M keys with average 24B key can consume multiple GB.
- Possible optimizations (as needed):
    - Use `flat_hash_map`/robin-hood hashing to reduce overhead.
    - Intern file path via `file_id` -> path table.
    - Key interning/arena to lower allocator fragmentation.
    - Store only key hashes or short prefixes (verify on read; risk of collisions).
    - Value size upcast to u64 if large values expected.

---

## Core Operations

### put(key, value)
- Append a record to the active file.
- Optionally `fsync` per write, or group commit (batch fsync).
- Update KeyDir to point to the new value.
- Rotate file if near `max_file_size`.

Semantics:
- With no `fsync`, last writes may be lost on crash; scan-based recovery restores any fully written record.

### get(key)
- Lookup KeyDir; if present, read `value_size` bytes from `(file_id, value_pos)`; return value.
- If absent, return not found.

### del(key)
- Append tombstone (value_size = 0).
- Remove key from KeyDir in memory.
- Tombstone stays on disk until compaction.

---

## Startup and Recovery

- Enumerate `.data` files (ascending by id).
- For each file:
    - If `.hint` exists and is valid: load it to populate KeyDir.
    - Else: sequentially scan the `.data` file:
        - Read `crc`, `timestamp`, `key_size`, `value_size`, then `key`, `value`.
        - Recompute CRC; stop at first mismatch/EOF (trailing partial).
        - Update KeyDir per record (tombstone removes; put updates).
- Design tolerates partial trailing records without special shutdown.

---

## Compaction (Merge)

Goal: reclaim space by eliminating overwritten values and tombstones; improve locality.

### Trigger policy
- Simple: run compaction when:
    - total immutable size > threshold, or
    - number of segments > N, or
    - space amplification exceeds threshold.
- Advanced: choose coldest or smallest segments; tiered/leveled strategies.

### Safe algorithm
- Snapshot KeyDir to define current winners.
- Choose source segments S (exclude the active file).
- For each key that has its latest version residing in S and is not shadowed by newer versions outside S:
    - Copy its latest value into a new output segment.
    - If the latest global version is a tombstone and all older versions are within S, drop it; otherwise, carry tombstone forward.
- Write a `.hint` for the new segment.
- Atomically install:
    - Update KeyDir to point to the new segment entries.
    - Delete old segments.
    - For stronger guarantees, fsync file and directory, and/or use a MANIFEST.

### Concurrency
- Reads continue during compaction using independent FDs.
- Writes go to active file; compactor must ensure copied entries are still current:
    - Options: snapshot epoch; or validate before install; or “verify then publish” by checking KeyDir during copy.

---

## Durability and fsync Strategy

- Modes:
    - `fsync` on every write: strongest consistency; higher latency.
    - Group commit: flush every T ms or every N operations.
    - `fsync` on rotation: acceptable if losing tail is tolerable; CRC-based recovery drops partial tails.
- For stronger consistency:
    - `fsync` new segments and the directory after creation/rename.
    - Consider barriers around compaction cutovers.

---

## Concurrency and Threading

- Single-writer, multi-reader simplifies invariants:
    - Writers update KeyDir under an exclusive lock.
    - Readers acquire shared lock on KeyDir entries or use lock-free reads with epoch protection if needed.
- Background compaction:
    - Runs in a dedicated thread.
    - Coordinate with the writer: mark selected segments as immutable/frozen; verify KeyDir entry freshness before publishing new segment.
- Cross-process:
    - Single writer enforced using a lock file.
    - Multiple readers can open files read-only.

---

## Configuration Knobs

- `max_file_size` for rotation.
- `fsync_each_write`, or `group_commit_ms`/`group_commit_ops`.
- Compaction triggers: `min_segments`, `size_threshold`, `amplification_ratio`, `coldness_threshold`.
- Read-ahead hints and FD cache sizes.
- Max key/value sizes and policy for oversize values.
- Optional:
    - Compression/encryption per segment.
    - Checksumming algorithm selection (CRC32, xxHash, etc.).

---

## Error Handling and Integrity

- Validate header bounds; reject absurd sizes.
- On CRC mismatch or partial read at EOF, stop scanning that file (treat as a torn/trailing record).
- Track and expose metrics:
    - Number of CRC errors, truncated bytes, recovered records, compaction stats.
- Ensure exceptions do not leave partial, untracked files:
    - Use temp filenames then atomic rename; fsync directories if necessary.

---

## Testing and Validation

- Functional:
    - put/get/del semantics and overwrites.
    - Delete behavior across compactions.
    - Edge cases: empty values, large keys/values, non-ASCII keys.
- Crash simulations:
    - Kill process at random points during put/rotate/compact; on restart, verify invariants and data survival per durability settings.
- Fuzzing:
    - Random byte flips; ensure recovery doesn’t crash and only discards trailing/corrupt records.
- Performance:
    - Append throughput, read latency distribution.
    - Compaction pause time and space amplification.
- Soak tests:
    - Long-running write/compact cycles; no FD leaks; steady-state footprint.

---

## MVP Scope

- Single-writer, single-thread compaction (manual trigger).
- Append-only `.data` segments with CRC-guarded records.
- In-memory KeyDir only (no hints).
- Startup rebuild by scanning segments; ignore trailing partials.
- Rotation by `max_file_size`.
- Basic API: `put`, `get`, `del`, `compact`, `sync`.

---

## Roadmap Enhancements

- Hint files for faster startup.
- Background compaction (subset selection; cold data first).
- Group commit and configurable durability modes.
- Lock file and cross-process R/O support.
- Memory-optimized KeyDir (flat hash map, arena, key hashing/prefix).
- File descriptor cache and read-ahead tuning.
- Optional compression and/or encryption.
- Metrics, tracing, fault injection hooks.
- TTL/expiration and iteration APIs if needed.

---

## Open Questions

Please confirm to tailor the design:

1. Scale: target number of keys and average key/value sizes?
2. Durability priority: fsync per write vs. group commit vs. rotate-only?
3. Concurrency: single process or multi-process readers; background compaction now or later?
4. Startup time budget: are hint files needed early?
5. Platform constraints: Linux-only or also Windows/macOS?
6. Extra features: TTL/expiration, iteration over keys, snapshots, batch writes?

Once these are clarified, we can lock down the on-disk format details (e.g., record_length, versioning), compaction policy, and KeyDir representation to fit your workloads and constraints.