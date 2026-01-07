#include <iostream>
#include <vector>
#include <queue>
#include "cache.h"

using namespace std;

struct CacheSet {
    vector<int> blocks;    
    queue<int> fifo;       
};

struct CacheLevel {
    int size;
    int blockSize;
    int ways;
    int numBlocks;
    int numSets;
    int latency;         

    vector<CacheSet> sets;

    int hits = 0;
    int misses = 0;
};

static CacheLevel L1, L2;


void initLevel(CacheLevel &c, int size, int ways, int blockSize, int latency) {
    c.size = size;
    c.blockSize = blockSize;
    c.ways = ways;
    c.latency = latency;

    c.numBlocks = size / blockSize;
    c.numSets = c.numBlocks / ways;

    c.sets.clear();
    c.sets.resize(c.numSets);

    c.hits = 0;
    c.misses = 0;
}

bool accessLevel(CacheLevel &c, int blockNumber, int &cycles) {
    int setIndex = blockNumber % c.numSets;
    CacheSet &set = c.sets[setIndex];

    // HIT check
    for (int b : set.blocks) {
        if (b == blockNumber) {
            c.hits++;
            cycles += c.latency;
            return true;
        }
    }

    // MISS
    c.misses++;
    cycles += c.latency;

    // FIFO replacement if set full
    if ((int)set.blocks.size() == c.ways) {
        int evict = set.fifo.front();
        set.fifo.pop();

        for (auto it = set.blocks.begin(); it != set.blocks.end(); it++) {
            if (*it == evict) {
                set.blocks.erase(it);
                break;
            }
        }
    }

    set.blocks.push_back(blockNumber);
    set.fifo.push(blockNumber);

    return false;
}



void initCache(
    int l1Size, int l1Ways,
    int l2Size, int l2Ways,
    int blockSize
) {
    initLevel(L1, l1Size, l1Ways, blockSize, 1);     
    initLevel(L2, l2Size, l2Ways, blockSize, 10);  
     
    cout << "Cache initialized\n";
    cout << "L1: " << L1.numSets << " sets, "
         << L1.ways << "-way, block size "
         << blockSize << ", latency "
         << L1.latency << " cycles\n";

    cout << "L2: " << L2.numSets << " sets, "
         << L2.ways << "-way, block size "
         << blockSize << ", latency "
         << L2.latency << " cycles\n";
}

void accessCache(int address) {
    int blockNumber = address / L1.blockSize;
    int cycles = 0;

    // L1 access
    if (accessLevel(L1, blockNumber, cycles)) {
        cout << "L1 HIT | cycles = " << cycles << endl;
        return;
    }

    cout << "L1 MISS\n";

    // L2 access
    if (accessLevel(L2, blockNumber, cycles)) {
        cout << "L2 HIT | cycles = " << cycles << endl;
        return;
    }

    cout << "L2 MISS\n";

    // Memory access penalty
    cycles += 100;
    cout << "MEMORY ACCESS | total cycles = " << cycles << endl;
}

void cacheStats() {
    cout << "\nCache Statistics\n";

    int l1Total = L1.hits + L1.misses;
    int l2Total = L2.hits + L2.misses;

    cout << "L1 -> Hits: " << L1.hits
         << ", Misses: " << L1.misses
         << ", Hit Ratio: "
         << (l1Total ? (double)L1.hits / l1Total * 100 : 0)
         << "%\n";

    cout << "L2 -> Hits: " << L2.hits
         << ", Misses: " << L2.misses
         << ", Hit Ratio: "
         << (l2Total ? (double)L2.hits / l2Total * 100 : 0)
         << "%\n";
}
