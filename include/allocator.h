#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <vector>

enum AllocatorType { FIRST_FIT, BEST_FIT, WORST_FIT };

struct Block {
    int start; //start index 
    int size; 
    bool free; 
    int id;
    int requestedSize;
};

void initMemory(int size);
void malloc(int size);
void freeBlock(int id);
void dumpMemory();
void showStats();
void setAllocator(AllocatorType type);



#endif
