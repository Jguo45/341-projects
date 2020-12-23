#include <iostream>
#include "queue.h"

using namespace std;

int main() {
    Queue<int> intQueue;
    Queue<int> assignmentQueue;
    Queue<int> emptyQueue;

    for (int i = 0; i <= 5; i++) {
        intQueue.enqueue(i);
    }

    cout << "=====Source Queue=====" << endl;
    cout << "intQueue Dump: " << endl;
    intQueue.dump();

    cout << "=====Source Copy Test=====" << endl;
    assignmentQueue = intQueue;
    cout << "assignmentQueue Dump: " << endl;
    assignmentQueue.dump();

    cout << "=====Deep Copy Test=====" << endl;
    intQueue.enqueue(10);
    assignmentQueue.enqueue(-10);
    cout << "intQueue: " << endl;
    intQueue.dump();
    cout << "assignmentQueue: " << endl;
    assignmentQueue.dump();

    cout << "=====Empty Assignment Test=====" << endl;
    assignmentQueue = emptyQueue;
    cout << "Empty: " << assignmentQueue.empty() << endl;

    cout << "=====Self Assignment Test=====" << endl;
    intQueue = intQueue;

    return 0;
}