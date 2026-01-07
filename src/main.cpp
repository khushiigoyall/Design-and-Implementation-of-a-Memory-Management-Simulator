#include <iostream>
#include "../include/allocator.h"
#include "../include/buddy.h"
#include "../include/cache.h"
#include "../include/virtual_memory.h"


using namespace std;

int main() {
    int size;
    cout << "Enter memory size: ";
    cin >> size;

    initMemory(size);
    cout << "Commands available:\n";
    cout << "\nAllocator Commands:\n";
    cout << "  malloc <size>\n";
    cout << "  free <block_id>\n";
    cout << "  dump\n";
    cout << "  stats\n";
    cout << "  exit\n";
    cout << "  set first|best|worst\n";
    cout << "\nBuddy Commands:\n";
    cout << "  initbuddy <size>\n";
    cout << "  buddyalloc <size>\n";
    cout << "  buddyfree <address>\n";
    cout << "  buddydump\n";
    cout << "\nCache Commands:\n";
    cout << "  initcache <L1size> <L1ways> <L2size> <L2ways> <blockSize>\n";
    cout << "  accesscache <address>\n";
    cout << "  cachestats\n";
    cout << "\nVirtual Memory Commands:\n";
    cout << "  initvm <virtualSize> <physicalSize> <pageSize>\n";
    cout << "  vmaccess <virtualAddress>\n";
    cout << "  vmstats\n";




    string command;

    while (true) {
        cout << "\n>";
        cin >> command;

        if (command == "malloc") {
            int s;
            cin >> s;
            malloc(s);
        }
        else if (command == "free") {
            int id;
            cin >> id;
            freeBlock(id);
        }
        else if (command == "dump") {
            dumpMemory();
        }
        else if (command == "exit") {
            break;
        }

        else if (command == "stats") {
            showStats();
        }

        else if (command == "set") {
    string type;
    cin >> type;

    if (type == "first") {
        setAllocator(FIRST_FIT);
    }
    else if (type == "best") {
        setAllocator(BEST_FIT);
    }
    else if (type == "worst") {
        setAllocator(WORST_FIT);
    }
    else {
        cout << "Unknown allocator type\n";
        return 0;
    }

    cout << "Allocator set to " << type << endl;
}


//buddy system 
else if (command == "initbuddy") {
    int s;
    cin >> s;
    initBuddy(s);
}
else if (command == "buddyalloc") {
    int s;
    cin >> s;
    buddyAlloc(s);
}
else if (command == "buddyfree") {
    int addr;
    cin >> addr;
    buddyFree(addr);
}
else if (command == "buddydump") {
    buddyDump();
}


//cache simulation
else if (command == "initcache") {
    int l1s, l1w, l2s, l2w, bs;
    cin >> l1s >> l1w >> l2s >> l2w >> bs;
    initCache(l1s, l1w, l2s, l2w, bs);
}
else if (command == "accesscache") {
    int addr;
    cin >> addr;
    accessCache(addr);
}
else if (command == "cachestats") {
    cacheStats();
}


else if (command == "initvm") {
    int v, p, ps;
    cin >> v >> p >> ps;
    initVirtualMemory(v, p, ps);
}
else if (command == "vmaccess") {
    int addr;
    cin >> addr;
    accessVirtualAddress(addr);
}
else if (command == "vmstats") {
    vmStats();
}





        else {
            cout << "Unknown command";
        }
    }

    return 0;
}
