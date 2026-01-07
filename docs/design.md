# 📘 DESIGN DOCUMENT

## Memory Management Simulator

---

## 1. Introduction

This project implements a **Memory Management Simulator** that demonstrates how memory is handled inside an operating system.
The simulator works through a command-line interface and allows users to interact with different memory subsystems such as **physical memory allocation**, **buddy allocation**, **CPU caching**, and **virtual memory paging**.

The purpose of this simulator is to convert operating system memory concepts into a **visible and understandable system**, where allocation decisions, cache behavior, and address translation can be observed directly.

---

## 2. System Overview

The simulator is structured into independent modules, each responsible for a specific memory management task. These modules communicate through a unified access flow.

```text
+----------------------------------+
|        User / CLI Commands        |
+----------------------------------+
                |
                v
+----------------------------------+
|        Command Controller         |
+----------------------------------+
      |            |            |
      v            v            v
Allocator       Buddy        Virtual Memory
                               |
                               v
                         Cache Subsystem
                               |
                               v
                         Physical Memory
```

Each subsystem can be tested independently, but together they form a complete memory access pipeline.

---

## 3. Physical Memory Layout and Assumptions

### Memory Model

Physical memory is simulated as **one contiguous block** of memory.
Each memory unit represents **one byte**, and memory addresses are treated as integer offsets.

```text
+------------------------------------------------------+
| Free | Alloc | Alloc | Free | Alloc | Free |  ...   |
+------------------------------------------------------+
```

### Block Representation

Each memory block maintains the following information:

| Attribute     | Description                    |
| ------------- | ------------------------------ |
| Block ID      | Unique ID for allocated blocks |
| Start Address | Starting memory index          |
| Size          | Block size in bytes            |
| Status        | Free or Allocated              |

### Assumptions

* Single-process execution
* No hardware-level interaction
* Dynamic memory partitioning
* Focus on correctness and visualization rather than performance

---

## 4. Allocation Strategy Implementations

The simulator supports **three classic dynamic memory allocation strategies**.

### Supported Strategies

| Strategy  | Behavior                                   |
| --------- | ------------------------------------------ |
| First Fit | Allocates the first suitable free block    |
| Best Fit  | Allocates the smallest suitable free block |
| Worst Fit | Allocates the largest available free block |

### Strategy Behavior

**First Fit**

```text
Scan memory from start → allocate first matching block
```

**Best Fit**

```text
Scan all free blocks → choose smallest suitable block
```

**Worst Fit**

```text
Scan all free blocks → choose largest free block
```

---

### Block Splitting

When a free block is larger than required, it is split into two parts.

```text
Before:
+-------------------- Free (100) --------------------+

After:
+----- Alloc (40) -----+------ Free (60) ------+
```

---

### Block Coalescing

When memory is freed, adjacent free blocks are merged.

```text
Before:
+---- Free ----+---- Free ----+

After:
+-------- Combined Free --------+
```

This helps reduce **external fragmentation**.

---

### Fragmentation Tracking

* **Internal Fragmentation**: unused space inside allocated blocks
* **External Fragmentation**: free memory split across non-adjacent blocks

---

## 5. Buddy Memory Allocation System

The buddy system is implemented as an alternative memory allocator using **power-of-two block sizes**.

### Buddy Memory Structure

```text
[ 1024 ]
 ├── 512
 │   ├── 256
 │   │   ├── 128
 │   │   └── 128
 │   └── 256
 └── 512
```

### Allocation Process

1. Requested size is rounded to the nearest power of two
2. Corresponding free list is searched
3. Larger blocks are split recursively if needed
4. Final block is allocated

### Buddy Identification

```text
buddy_address = block_address XOR block_size
```

This allows fast detection of mergeable buddy blocks.

### Buddy Coalescing

```text
Two free buddies of size 64 → merged into one block of size 128
```

---

## 6. Virtual Memory System

Virtual memory is implemented using **paging**.

### Virtual Address Structure

```text
+----------------------+----------------+
| Page Number          | Offset         |
+----------------------+----------------+
```

### Page Table Design

Each virtual page maps to a page table entry:

| Field        | Description                  |
| ------------ | ---------------------------- |
| Valid Bit    | Indicates presence in memory |
| Frame Number | Physical frame index         |

---

### Page Replacement Policy

* FIFO (First-In-First-Out)
* Oldest loaded page is evicted on a page fault
* Page hits and page faults are tracked

---

## 7. Cache Hierarchy and Replacement Policy

The simulator models a **two-level CPU cache hierarchy** placed between the CPU and main memory.

### Cache Hierarchy

```text
CPU
 |
 v
+----- L1 Cache -----+
 |
 v
+----- L2 Cache -----+
 |
 v
Main Memory
```

### Cache Organization

| Property    | Description     |
| ----------- | --------------- |
| Levels      | L1 and L2       |
| Mapping     | Set-associative |
| Replacement | FIFO            |
| Sizes       | Configurable    |

---

### Cache Access Flow

```text
Check L1
 ├─ Hit → Return
 └─ Miss → Check L2
        ├─ Hit → Update L1
        └─ Miss → Fetch from Memory
```

### Replacement Policy

FIFO replacement removes the **oldest cache line** within a set when space is needed.

---

### Miss Propagation and Statistics

* L1 misses propagate to L2
* L2 misses propagate to memory
* Hit/miss counts tracked per level
* Total access cycles calculated

---

## 8. Address Translation Flow

All memory accesses follow a fixed translation pipeline:

```text
Virtual Address
      |
      v
Page Table Lookup
      |
      v
Physical Address
      |
      v
L1 Cache → L2 Cache
      |
      v
Main Memory
```

This flow allows observation of:

* Page faults
* Cache hit/miss behavior
* Physical memory access patterns

---

## 9. Limitations and Simplifications

The simulator includes the following simplifications:

| Limitation           | Description         |
| -------------------- | ------------------- |
| Process model        | Single-process only |
| Replacement policies | FIFO only           |
| Disk access          | Symbolic            |
| Concurrency          | Not supported       |
| Hardware accuracy    | Abstracted          |

---

## 10. Conclusion

The Memory Management Simulator provides a structured and visual representation of how memory is managed inside an operating system. By integrating allocation strategies, caching, and virtual memory into a single system, it enables clear observation of memory behavior and subsystem interaction.

---

