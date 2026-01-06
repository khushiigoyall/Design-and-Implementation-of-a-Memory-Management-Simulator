#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <vector>

struct Block {
    int start; //start index 
    int size; 
    bool free; 
    int id;
};

void initMemory(int size);
void mallocFF(int size);
void freeBlock(int id);
void dumpMemory();

#endif
