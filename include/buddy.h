#ifndef BUDDY_H
#define BUDDY_H

void initBuddy(int size);
int buddyAlloc(int size);
void buddyFree(int address);
void buddyDump();

#endif
