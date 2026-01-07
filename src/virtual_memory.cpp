#include <iostream>
#include <vector>
#include <queue>
#include "virtual_memory.h"
#include "cache.h"

using namespace std;

struct PageTableEntry {
    bool valid;
    int frameNumber;
};

static vector<PageTableEntry> pageTable;
static queue<int> fifoQueue;

static int VIRTUAL_MEM_SIZE;
static int PHYSICAL_MEM_SIZE;
static int PAGE_SIZE;

static int NUM_PAGES;
static int NUM_FRAMES;

static int pageHits = 0;
static int pageFaults = 0;


void initVirtualMemory(
    int virtualMemorySize,
    int physicalMemorySize,
    int pageSize
) {
    VIRTUAL_MEM_SIZE = virtualMemorySize;
    PHYSICAL_MEM_SIZE = physicalMemorySize;
    PAGE_SIZE = pageSize;

    NUM_PAGES = VIRTUAL_MEM_SIZE / PAGE_SIZE;
    NUM_FRAMES = PHYSICAL_MEM_SIZE / PAGE_SIZE;

    pageTable.clear();
    pageTable.resize(NUM_PAGES);

    while (!fifoQueue.empty()) fifoQueue.pop();

    for (auto &entry : pageTable) {
        entry.valid = false;
        entry.frameNumber = -1;
    }

    pageHits = 0;
    pageFaults = 0;

    cout << "Virtual Memory Initialized\n";
    cout << "Pages: " << NUM_PAGES
         << ", Frames: " << NUM_FRAMES
         << ", Page Size: " << PAGE_SIZE << endl;
}


void accessVirtualAddress(int virtualAddress) {
    int pageNumber = virtualAddress / PAGE_SIZE;
    int offset = virtualAddress % PAGE_SIZE;

    if (pageNumber >= NUM_PAGES) {
        cout << "Invalid virtual address\n";
        return;
    }

    if (pageTable[pageNumber].valid) {
        pageHits++;
        int frame = pageTable[pageNumber].frameNumber;
        int physicalAddress = frame * PAGE_SIZE + offset;

        cout << "PAGE HIT | VA " << virtualAddress
             << " → PA " << physicalAddress << endl;

        accessCache(physicalAddress);
        return;
    }

 
    pageFaults++;
    cout << "PAGE FAULT for page " << pageNumber << endl;

    int frame;


    if ((int)fifoQueue.size() < NUM_FRAMES) {
        frame = fifoQueue.size();
    }
    else {
      
        int victimPage = fifoQueue.front();
        fifoQueue.pop();

        frame = pageTable[victimPage].frameNumber;
        pageTable[victimPage].valid = false;

        cout << "Evicted page " << victimPage << endl;
    }


    pageTable[pageNumber].valid = true;
    pageTable[pageNumber].frameNumber = frame;
    fifoQueue.push(pageNumber);

    int physicalAddress = frame * PAGE_SIZE + offset;

    cout << "Loaded page " << pageNumber
         << " into frame " << frame
         << " | PA " << physicalAddress << endl;

    // Simulated disk latency (symbolic)
    cout << "Disk access latency = 100 cycles\n";

 
    accessCache(physicalAddress);
}



void vmStats() {
    int total = pageHits + pageFaults;

    cout << "\nVirtual Memory Statistics\n";
    cout << "Page Hits: " << pageHits << endl;
    cout << "Page Faults: " << pageFaults << endl;
    cout << "Hit Ratio: "
         << (total ? (double)pageHits / total * 100 : 0)
         << "%\n";
}
