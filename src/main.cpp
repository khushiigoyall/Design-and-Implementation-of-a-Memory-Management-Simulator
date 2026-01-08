#include <iostream>
#include <string>

#include "../include/allocator.h"
#include "../include/buddy.h"
#include "../include/cache.h"
#include "../include/virtual_memory.h"

using namespace std;

// --------------------------------------------------
void printBanner() {
    cout << "\n=================================================\n";
    cout << "        MEMORY MANAGEMENT SIMULATOR\n";
    cout << "=================================================\n";
    cout << "[INFO] Simulator started\n\n";
}

// --------------------------------------------------
void printCommands() {
    cout << "\n---------------- AVAILABLE COMMANDS ----------------\n";

    cout << "\n[ Allocator Commands ]\n";
    cout << "  malloc <size>\n";
    cout << "  free <block_id>\n";
    cout << "  dump\n";
    cout << "  stats\n";
    cout << "  set first | best | worst\n";

    cout << "\n[ Buddy System Commands ]\n";
    cout << "  initbuddy <size>\n";
    cout << "  buddyalloc <size>\n";
    cout << "  buddyfree <address>\n";
    cout << "  buddydump\n";

    cout << "\n[ Cache Commands ]\n";
    cout << "  initcache <L1size> <L1ways> <L2size> <L2ways> <blockSize>\n";
    cout << "  accesscache <address>\n";
    cout << "  cachestats\n";

    cout << "\n[ Virtual Memory Commands ]\n";
    cout << "  initvm <virtualSize> <physicalSize> <pageSize>\n";
    cout << "  vmaccess <virtualAddress>\n";
    cout << "  vmstats\n";

    cout << "\n[ General ]\n";
    cout << "  help\n";
    cout << "  exit\n";

    cout << "----------------------------------------------------\n";
}

// --------------------------------------------------
void printSection(const string &title) {
    cout << "\n=====================================\n";
    cout << "   " << title << "\n";
    cout << "=====================================\n";
}

int main() {
    printBanner();

    int size;
    cout << "Enter initial physical memory size: ";
    cin >> size;
    initMemory(size);

    printCommands();

    string command;

    while (true) {
        cout << "\n[memsim] > ";
        cin >> command;

        // ---------------- GENERAL ----------------
        if (command == "exit") {
            printSection("EXITING SIMULATOR");
            cout << "Simulator stopped.\n";
            break;
        }

        else if (command == "help") {
            printCommands();
        }

        // ---------------- ALLOCATOR ----------------
        else if (command == "malloc") {
            int s;
            cin >> s;
            printSection("MEMORY ALLOCATION");
            cout << "Request size: " << s << "\n";
            malloc(s);
        }

        else if (command == "free") {
            int id;
            cin >> id;
            printSection("MEMORY DEALLOCATION");
            cout << "Block ID: " << id << "\n";
            freeBlock(id);
        }

        else if (command == "dump") {
            printSection("MEMORY DUMP");
            dumpMemory();
        }

        else if (command == "stats") {
            printSection("MEMORY STATISTICS");
            showStats();
        }

        else if (command == "set") {
            string type;
            cin >> type;
            printSection("ALLOCATOR STRATEGY");

            if (type == "first") setAllocator(FIRST_FIT);
            else if (type == "best") setAllocator(BEST_FIT);
            else if (type == "worst") setAllocator(WORST_FIT);
            else {
                cout << "Unknown allocator type\n";
                continue;
            }

            cout << "Strategy set to: " << type << "\n";
        }

        // ---------------- BUDDY SYSTEM ----------------
        else if (command == "initbuddy") {
            int s;
            cin >> s;
            printSection("BUDDY SYSTEM INITIALIZATION");
            initBuddy(s);
        }

        else if (command == "buddyalloc") {
            int s;
            cin >> s;
            printSection("BUDDY ALLOCATION");
            buddyAlloc(s);
        }

        else if (command == "buddyfree") {
            int addr;
            cin >> addr;
            printSection("BUDDY DEALLOCATION");
            buddyFree(addr);
        }

        else if (command == "buddydump") {
            printSection("BUDDY MEMORY DUMP");
            buddyDump();
        }

        // ---------------- CACHE ----------------
        else if (command == "initcache") {
            int l1s, l1w, l2s, l2w, bs;
            cin >> l1s >> l1w >> l2s >> l2w >> bs;
            printSection("CACHE INITIALIZATION");
            initCache(l1s, l1w, l2s, l2w, bs);
        }

        else if (command == "accesscache") {
            int addr;
            cin >> addr;
            printSection("CACHE ACCESS");
            accessCache(addr);
        }

        else if (command == "cachestats") {
            printSection("CACHE STATISTICS");
            cacheStats();
        }

        // ---------------- VIRTUAL MEMORY ----------------
        else if (command == "initvm") {
            int v, p, ps;
            cin >> v >> p >> ps;
            printSection("VIRTUAL MEMORY INITIALIZATION");
            initVirtualMemory(v, p, ps);
        }

        else if (command == "vmaccess") {
            int addr;
            cin >> addr;
            printSection("VIRTUAL MEMORY ACCESS");
            accessVirtualAddress(addr);
        }

        else if (command == "vmstats") {
            printSection("VIRTUAL MEMORY STATISTICS");
            vmStats();
        }

        // ---------------- UNKNOWN ----------------
        else {
            cout << "[ERROR] Unknown command. Type 'help' to see commands.\n";
        }
    }

    return 0;
}
