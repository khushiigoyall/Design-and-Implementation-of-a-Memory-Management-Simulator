#include <iostream>
#include "../include/allocator.h"

using namespace std;

int main() {
    int size;
    cout << "Enter memory size: ";
    cin >> size;

    initMemory(size);
    cout << "Commands available:\n";
    cout << "  malloc          - allocate memory\n";
    cout << "  free            - free allocated block\n";
    cout << "  dump            - show memory layout\n";
    cout << "  exit            - quit program\n\n";

    string command;

    while (true) {
        cout << "\n> enter command :";
        cin >> command;

        if (command == "malloc") {
            int s;
            cout<<"enter rquired size : ";
            cin >> s;
            mallocFF(s);
        }
        else if (command == "free") {
            int id;
            cout<<"enter id of used block: ";
            cin >> id;
            freeBlock(id);
        }
        else if (command == "dump") {
            dumpMemory();
        }
        else if (command == "exit") {
            break;
        }
        else {
            cout << "Unknown command";
        }
    }

    return 0;
}
