# 🧠 Memory Management Simulator

## Overview

The **Memory Management Simulator** is a command-line–based educational project that demonstrates how an operating system manages memory internally.  
It simulates multiple memory management components, including **physical memory allocation**, **buddy allocation**, **CPU cache hierarchy**, and **virtual memory with paging**.

The goal of this project is to provide a clear and practical understanding of memory management concepts through interactive commands and observable system behavior.

---

## Features

- Dynamic physical memory allocation
  - First Fit
  - Best Fit
  - Worst Fit
- Block splitting and coalescing
- Fragmentation analysis and memory statistics
- Buddy memory allocation system (power-of-two based)
- Multi-level CPU cache simulation
  - L1 and L2 caches
  - Set-associative mapping
  - FIFO replacement policy
- Virtual memory using paging
  - Page tables
  - FIFO page replacement
  - Page hit and page fault tracking
- Integrated memory access pipeline:  
  **Virtual Address → Page Table → Cache → Physical Memory**

---

## Project Structure
```text
memory-management-simulator/
├── src/
│ ├── main.cpp
│ ├── allocator.cpp
│ ├── buddy.cpp
│ ├── cache.cpp
│ └── virtual_memory.cpp
│
├── include/
│ ├── allocator.h
│ ├── buddy.h
│ ├── cache.h
│ └── virtual_memory.h
│
├── tests/
│ ├── allocator_test.txt
│ ├── buddy_test.txt
│ ├── cache_test.txt
│ ├── virtual_memory_test.txt
│ └── integration_test.txt
│
├── docs/
│ └── design.md
│
├── Makefile
└── README.md
```

---

## Build Instructions

This project uses a **Makefile** for compilation.

### Requirements

- C++ compiler (GCC recommended)
- GNU Make

### Compile

```bash
make
./memory_simulator.exe
make clean
```

## Command Interface

### Memory Allocator Commands
```text
malloc <size>
free <block_id>
dump
stats
set first | best | worst
```
### Buddy System Commands
```text
initbuddy <size>
buddyalloc <size>
buddyfree <address>
buddydump
```
### Cache Simulation Commands
```text
initcache <L1size> <L1ways> <L2size> <L2ways> <blockSize>
accesscache <address>
cachestats
```

### Virtual Memory Commands
```text
initvm <virtualSize> <physicalSize> <pageSize>
vmaccess <virtualAddress>
vmstats
```

## Tests
Test artifacts are provided in the tests/ directory.

Each test file contains:
- Input command sequences
- Observed behavior summary
- Expected correctness criteria

The tests cover:
- Memory allocation and deallocation
- Buddy system behavior
- Cache hit/miss behavior
- Virtual memory page faults and hits
- Integrated memory access flow

## Design Documentation
A detailed design document describing:

- Memory layout and assumptions
- Allocation strategies
- Buddy system design
- Cache hierarchy and replacement policy
- Virtual memory model
- Address translation flow
- Limitations and simplifications
```text
docs/design.md
```

## Assumptions and Limitations
- Single-process simulation
- FIFO replacement policies only
- No real disk or hardware interaction
- No concurrency or multithreading
- Timing values are illustrative

## Purpose
This simulator is intended for learning and academic use, helping users understand how different memory management components interact inside an operating system.
