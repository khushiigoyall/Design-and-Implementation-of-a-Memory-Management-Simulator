#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include "buddy.h"
#include <algorithm>
#include <unordered_map>


using namespace std;
static map<int, vector<int>> freeList;
static int totalSize;
static unordered_map<int, int> allocatedBlocks;



void initBuddy(int size) {
    freeList.clear();
    totalSize = size;
    freeList[size].push_back(0);

    cout << "Buddy system initialized with size " << size << endl;
}


int nextPowerOfTwo(int n) {
    int power = 1;
    while (power < n)
        power *= 2;
    return power;
}


int buddyAlloc(int size) {
    int reqSize = nextPowerOfTwo(size);

    int currSize = reqSize;
    while (currSize <= totalSize && freeList[currSize].empty()) {
        currSize *= 2;
    }

    if (currSize > totalSize) {
        cout << "Buddy allocation failed\n";
        return -1;
    }

 
    int address = freeList[currSize].back();
    freeList[currSize].pop_back();


    while (currSize > reqSize) {
        currSize /= 2;
        int buddyAddr = address + currSize;
        freeList[currSize].push_back(buddyAddr);
    }

    cout << "Allocated buddy block at address " << address
         << " of size " << reqSize << endl;

    allocatedBlocks[address] = reqSize;
    return address;
}



void buddyFree(int address) {
    int size = allocatedBlocks[address];
    allocatedBlocks.erase(address);

    int currSize = size;

    while (currSize < totalSize) {
        int buddyAddr = address ^ currSize;

        auto &list = freeList[currSize];
        auto it = find(list.begin(), list.end(), buddyAddr);

        if (it == list.end())
            break;

        list.erase(it);
        address = min(address, buddyAddr);
        currSize *= 2;
    }

    freeList[currSize].push_back(address);

    cout << "Block freed and merged at address "
         << address << " with size " << currSize << endl;
}



void buddyDump() {
    cout << "\nBuddy Free Lists:\n";
    for (auto &entry : freeList) {
        cout << "Size " << entry.first << ": ";
        for (int addr : entry.second)
            cout << addr << " ";
        cout << endl;
    }
}


