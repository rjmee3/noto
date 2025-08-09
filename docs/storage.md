# Storage Design for Custom VCS

## Overview

This document outlines the storage architecture for a custom version control system (VCS). It is designed for efficiency, integrity, and fast querying. The system uses a patch-based internal history while maintaining Git-like commits and tree structures, SHA-256 hashes for object identity, and packfiles for compact storage.

---

## Stored Entities

| Entity        | Description                                   |
| ------------- | --------------------------------------------- |
| **Blobs**     | Raw file contents                             |
| **Patches**   | Diffs between file versions                   |
| **Trees**     | Directory snapshots referencing other objects |
| **Commits**   | Metadata + patchset + parent refs             |
| **Refs**      | Named pointers to commits (e.g. branches)     |
| **Packfiles** | Containers for compressed objects             |

---

## Object Model

All versioned data is stored as objects:

* **Addressed by SHA-256 hash**
* **Typed:** blob, patch, tree, commit
* **Payloads:** Binary data, optionally compressed

### Object Hashing Format

```
SHA256(type || length || payload)
```

Ensures content integrity and deduplication.

---

## Directory Layout

```
.myvcs/
├── objects/
│   ├── pack/
│   │   ├── pack-<hash>.pack
│   │   └── pack-<hash>.idx
├── refs/
│   ├── heads/
│   └── tags/
├── HEAD
├── config
└── tokens/
```

---

## Packfile Format

Packfiles store multiple objects in binary form to save space and improve performance.

### Structure:

```
[PACK HEADER]
[OBJECT ENTRY 1]
[OBJECT ENTRY 2]
...
[PACK TRAILER]
```

### Pack Header

| Field   | Size | Notes             |
| ------- | ---- | ----------------- |
| Magic   | 4    | 'PACK'            |
| Version | 2    | Version number    |
| Count   | 4    | Number of objects |

### Object Entry

| Field   | Size     | Description                       |
| ------- | -------- | --------------------------------- |
| Type    | 1 byte   | 1=blob, 2=patch, 3=tree, 4=commit |
| Length  | VarInt   | Payload size                      |
| Hash    | 32 bytes | SHA-256 hash                      |
| Payload | Variable | Raw or compressed binary data     |

### Optional Trailer

* File checksum
* Offset index pointer

---

## Index File (.idx)

Accelerates object lookups without full file scans.

| Field               | Size     | Description                 |
| ------------------- | -------- | --------------------------- |
| Count               | 4 bytes  | Number of entries           |
| \[Hash, Offset] x N | 36 bytes | 32-byte SHA + 4-byte offset |

---

## Object Definitions

### Blob

Raw file contents.

```cpp
struct Blob {
    std::vector<uint8_t> data;
};
```

### Patch

Delta between two file versions.

```cpp
struct Patch {
    std::string base_blob_hash;
    std::vector<DiffChunk> chunks;
};
```

### Tree

Recursive directory snapshot.

```cpp
struct TreeEntry {
    std::string name;
    std::string hash;
    uint8_t type;
};

struct Tree {
    std::vector<TreeEntry> entries;
};
```

### Commit

Versioned snapshot + metadata.

```cpp
struct Commit {
    std::string author;
    std::string message;
    std::string timestamp;
    std::string tree_hash;
    std::vector<std::string> parent_hashes;
    std::vector<std::string> patch_hashes;
};
```

---

## Object Lifecycle

1. **Commit:**

   * Detect file changes
   * Generate patches/blobs
   * Create tree and commit
   * Save to packfile

2. **Checkout:**

   * Read commit
   * Reconstruct tree
   * Apply patches to blobs
   * Write files to disk

3. **Sync:**

   * Exchange object graphs
   * Transmit missing objects via packfile

---

## Serialization Format

* Binary format for compactness
* Little-endian integers
* UTF-8 for strings
* Compression via zlib (future: pluggable)

---

## Integrity & GC

* SHA-256 guarantees integrity
* Checksums verify packfiles
* Future: garbage collection for unreferenced objects

---

## Testing

* Unit tests per object type
* End-to-end: commit → packfile → checkout
* Fuzz tests for packfile loader

---

## Notes

* Patch granularity: line-level (for now)
* Index caching: load into memory for performance
* Locking: writes use file locks, reads are lock-free
* Future: delta compression for patches and blobs
