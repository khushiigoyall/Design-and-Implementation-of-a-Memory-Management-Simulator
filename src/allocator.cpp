#include <iostream>
#include "../include/allocator.h"
#include <climits>


using namespace std;

static vector<Block> blocks;
static int memorySize;
static int nextId = 1;
static AllocatorType currentAllocator = FIRST_FIT;
static int totalAllocRequests = 0;
static int failedAllocRequests = 0;



void setAllocator(AllocatorType type) {
    currentAllocator = type;
}


// Initializes memory with one large free block
void initMemory(int size) {
    blocks.clear();
    memorySize = size;

    Block first;
    first.start = 0;
    first.size = size;
    first.free = true;
    first.id = -1;
    first.requestedSize = 0;


    blocks.push_back(first);
}

// Allocates memory using selected strategy
void malloc(int reqSize) {
    int index = -1;
    totalAllocRequests++;


    if (currentAllocator == FIRST_FIT) {
        for (size_t i= 0; i < blocks.size(); i++) {
            if (blocks[i].free && blocks[i].size >= reqSize) {
                index = i;
                break;
            }
        }
    }
    else if (currentAllocator == BEST_FIT) {
        int bestSize = INT_MAX;
        for (size_t i = 0; i < blocks.size(); i++) {
            if (blocks[i].free && blocks[i].size >= reqSize &&
                blocks[i].size < bestSize) {
                bestSize = blocks[i].size;
                index = i;
            }
        }
    }
    else if (currentAllocator == WORST_FIT) {
        int worstSize = -1;
        for (size_t i = 0; i < blocks.size(); i++) {
            if (blocks[i].free && blocks[i].size >= reqSize &&
                blocks[i].size > worstSize) {
                worstSize = blocks[i].size;
                index = i;
            }
        }
    }

    if (index == -1) {
        failedAllocRequests++;
        cout << "Allocation failed\n";

        return;
    }

Block used;
used.start = blocks[index].start;
used.size = reqSize;
used.requestedSize = reqSize;
used.free = false;
used.id = nextId++;


    blocks[index].start += reqSize;
    blocks[index].size -= reqSize;

    blocks.insert(blocks.begin() + index, used);

    if (blocks[index + 1].size == 0)
        blocks.erase(blocks.begin() + index + 1);

    cout << "Allocated block id=" << used.id << endl;
}



// Frees a block and merges adjacent free blocks
void freeBlock(int id) {
    for (size_t i = 0; i < blocks.size(); i++) {
        if (!blocks[i].free && blocks[i].id == id) {

            blocks[i].free = true;
            blocks[i].id = -1;
            blocks[i].requestedSize = 0;


            if (i> 0 && blocks[i - 1].free) {
                blocks[i - 1].size += blocks[i].size;
                blocks.erase(blocks.begin() + i);
                i--;
            }

            if (i< blocks.size() - 1 && blocks[i + 1].free) {
                blocks[i].size += blocks[i + 1].size;
                blocks.erase(blocks.begin() + i + 1);
            }

            cout << "Block is free now" << endl;
            return;
        }
    }

    cout << "Block not found" << endl;
}

// Displays current memory layout
void dumpMemory() {
    cout << "\nMemory Layout:\n";
    for (auto b : blocks) {
        cout << "[" << b.start << " - "
             << b.start + b.size - 1 << "] ";

        if (b.free)
            cout << "FREE";
        else
            cout << "USED (id=" << b.id << ")";

        cout << endl;
    }
}

//displays memory statistics
void showStats() {
    int used = 0;
    int freeMem = 0;
    int largestFree = 0;
    int internalFrag = 0;

    for (auto b : blocks) {
        if (b.free) {
            freeMem += b.size;
            if (b.size > largestFree)
                largestFree = b.size;
        } else {
            used += b.size;
            internalFrag += (b.size - b.requestedSize);
        }
    }

    double externalFrag = 0;
    if (freeMem > 0) {
        externalFrag =
            (double)(freeMem - largestFree) / freeMem * 100;
    }

    int successAlloc = totalAllocRequests - failedAllocRequests;
    double successRate = totalAllocRequests == 0 ? 0 :
        (double)successAlloc / totalAllocRequests * 100;

    double utilization = (double)used / memorySize * 100;

    cout << "\nMemory Statistics:\n";
    cout << "Total Memory: " << memorySize << endl;
    cout << "Used Memory: " << used << endl;
    cout << "Free Memory: " << freeMem << endl;

    cout << "Memory Utilization: " << utilization << "%\n";

    cout << "Internal Fragmentation: "
         << internalFrag << endl;

    cout << "External Fragmentation: "
         << externalFrag << "%\n";

    cout << "Allocation Requests: " << totalAllocRequests << endl;
    cout << "Failed Allocations: " << failedAllocRequests << endl;
    cout << "Allocation Success Rate: "
         << successRate << "%\n";
}

