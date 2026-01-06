#include <iostream>
#include "../include/allocator.h"

using namespace std;

static vector<Block> blocks;
static int memorySize;
static int nextId = 1;

void initMemory(int size) {
    blocks.clear();
    memorySize = size;

    Block first;
    first.start = 0;
    first.size = size;
    first.free = true;
    first.id = -1;

    blocks.push_back(first);
}


void mallocFF(int reqSize) {
    for (int i = 0; i < blocks.size(); i++) {
        if (blocks[i].free && blocks[i].size >= reqSize) {

            Block used;
            used.start = blocks[i].start;
            used.size = reqSize;
            used.free = false;
            used.id = nextId++;

            blocks[i].start += reqSize;
            blocks[i].size -= reqSize;

            blocks.insert(blocks.begin() + i, used);

            if (blocks[i + 1].size == 0) {
                blocks.erase(blocks.begin() + i + 1);
            }

            cout << "Allocated block id=" << used.id << endl;
            return;
        }
    }

    cout << "Allocation failed" << endl;
}


void freeBlock(int id) {
    for (int i = 0; i < blocks.size(); i++) {
        if (!blocks[i].free && blocks[i].id == id) {

            blocks[i].free = true;
            blocks[i].id = -1;

            if (i > 0 && blocks[i - 1].free) {
                blocks[i - 1].size += blocks[i].size;
                blocks.erase(blocks.begin() + i);
                i--;
            }

            if (i < blocks.size() - 1 && blocks[i + 1].free) {
                blocks[i].size += blocks[i + 1].size;
                blocks.erase(blocks.begin() + i + 1);
            }

            cout << "Block is free now" << endl;
            return;
        }
    }

    cout << "Block not found" << endl;
}


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
