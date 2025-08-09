# MyVCS Design Document

## Overview

**MyVCS** is a decentralized-friendly, high-performance version control system inspired by Git, but with a more patch-oriented approach to history representation. It aims to be self-hostable, modular, and extensible, with symmetric sync protocols and efficient storage for long-term scalability.

---

## Table of Contents

1. [Goals](#goals)
2. [Core Concepts](#core-concepts)
3. [Storage Model](#storage-model)
4. [Repository Layout](#repository-layout)
5. [Commit & History Model](#commit--history-model)
6. [Hashing](#hashing)
7. [Authentication](#authentication)
8. [Sync Model](#sync-model)
9. [Protocol](#protocol)
10. [CLI Design](#cli-design)
11. [Merge Model](#merge-model)
12. [Testing & Logging](#testing--logging)
13. [Future Directions](#future-directions)

---

## Goals

- Provide a fast, structured VCS with a patch-based internal model.
- Support Git-style workflows with centralized remotes and future P2P sync.
- Ensure robust performance via binary protocols and packfile-based storage.
- Offer self-hostable, secure synchronization with an extensible auth system.
- Maintain readable commit history structured as trees with commits.

---

## Core Concepts

- **Blob**: Represents file contents (deduplicated via hash).
- **Patch**: Encodes file-level changes (diffs) with reference to a base.
- **Tree**: Represents a snapshot of the directory structure (like Git).
- **Commit**: Metadata + patchset + pointer(s) to parent commit(s) + tree root.
- **Packfile**: Binary-encoded bundle of versioned objects (blobs, trees, commits, patches) with fast index lookup.

---

## Storage Model

### Object Storage

- All versioned entities (blobs, trees, patches, commits) are stored as binary-encoded objects.
- Object identifiers are content-addressed (SHA-256).
- Objects are grouped into **packfiles** to improve performance and reduce I/O.

### Packfile Format

Each `.pack` file includes:

- Object count
- Object metadata table (hash, type, offset)
- Compressed binary data section
- Optional index file for quick lookup

### Rationale

- Packfiles allow efficient read access and compact storage.
- Suitable for large-scale repositories and fast sync.

---

## Repository Layout

.myvcs/
├── objects/
│ └── pack/
│   ├── pack-abc123.pack
│   └── pack-abc123.idx
├── refs/
│ ├── heads/
│ │ └── main
│ └── tags/
├── HEAD
├── config
└── tokens/ # Optional, for token-based auth


---

## Commit & History Model

- History is structured as a **DAG** of commits.
- Commits store:
  - Author, timestamp, message
  - Pointer to base commit(s)
  - Tree reference (snapshot of working state)
  - Patchset (diffs applied to base commit(s))

This hybrid model provides:
- Patch-level tracking for performance and semantic diffs
- Tree-level control for readability and quick traversal

---

## Hashing

- All objects are addressed using **SHA-256**.
- Content hash is computed on the serialized binary representation of the object.
- Guarantees content integrity and deduplication.

---

## Authentication

### Phase 1: Token-Based Authentication
- Clients authenticate using a shared secret token.
- Each remote server maintains a list of valid tokens.
- Tokens can be scoped to read/write capabilities.

### Phase 2: mTLS (Planned)
- Future versions will support mutual TLS between peers.
- Token-based structure will be abstracted in an `AuthManager` interface.
- This will allow a smooth transition to pluggable authentication backends.

---

## Sync Model

### Git-Style Remotes (Default)
- Clients define named remotes (`origin`, `backup`, etc.).
- Commands like `myvcs push origin` and `myvcs pull peer1` are supported.

### P2P Compatibility
- The sync protocol is **symmetric** by design.
- Any node can initiate or respond to sync requests.
- Nodes can optionally auto-discover other nodes using mDNS or static config.

---

## Protocol

- The sync protocol uses a **custom binary format** for performance.
- Communication is over HTTP/2, QUIC, or raw TCP (pluggable).
- All messages are:
  - Length-prefixed
  - Type-tagged (e.g., PUSH_REQUEST, OBJECT_DATA, DONE)
  - Serialized as binary structs with headers

### Example Sync Flow

1. Client: Sends `SyncRequest` with current `HEAD`.
2. Server: Responds with missing commits/tree/patch objects.
3. Client: Streams objects in binary format.
4. Server: Validates and updates object store.

---

## CLI Design

- Commands follow a **Git-style subcommand model**:
  - `myvcs init`
  - `myvcs commit -m "message"`
  - `myvcs status`
  - `myvcs push origin`
  - `myvcs pull peer1`

### Subcommand Framework
- CLI uses argument parser (e.g., CLI11 or custom).
- Each subcommand is modular and testable.

---

## Merge Model

- **Three-way line-level merge**:
  - Base commit (common ancestor)
  - Local changes (ours)
  - Remote changes (theirs)

### Conflict Detection
- If overlapping line changes are detected, the system flags a conflict.
- Future versions may support:
  - Semantic merges
  - File-level strategies
  - Auto-merge plugins

---

## Testing & Logging

### Testing
- All logic is unit tested using **Google Test**.
- Integration tests validate full command workflows.
- Packfile parsing and sync protocol are fuzz-tested.

### Logging
- Macro-based logger with log levels (INFO, DEBUG, ERROR)
- Logs go to stdout or a rotating file
- Structured logs can be added later (JSON format for observability)

---

## Future Directions

- Support for rebasing, cherry-pick, bisect
- Web UI dashboard (status, history, sync logs)
- Cryptographic signing of commits
- Configurable storage backends (SQLite, S3)
- GUI client
- Plugin API (e.g., merge drivers, object filters)

---

## Appendix: Open Questions

- How to serialize patches efficiently?
- Should packfiles support delta compression?
- What is the default line-ending policy (CRLF/Unix)?
- Will we support Windows, Linux, and macOS equally?
- What concurrency model will the sync daemon use?

---

## Author

- Design by: Russ M
- Project: MyVCS
- License: MIT or Apache 2.0 (TBD)

