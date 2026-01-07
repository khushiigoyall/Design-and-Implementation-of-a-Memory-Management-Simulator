#ifndef VIRTUAL_MEMORY_H
#define VIRTUAL_MEMORY_H

void initVirtualMemory(
    int virtualMemorySize,
    int physicalMemorySize,
    int pageSize
);

void accessVirtualAddress(int virtualAddress);

void vmStats();

#endif
