#ifndef CACHE_H
#define CACHE_H

void initCache(
    int l1Size, int l1Ways,
    int l2Size, int l2Ways,
    int blockSize
);

// Access memory l1 to l2 to memory
void accessCache(int address);

void cacheStats();

#endif
