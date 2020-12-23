#include <iostream>
#include "heap.h"
#include "hash.h"
#include "car.h"
using namespace std;

const string FAIL = "******TEST FAILED";
const string PASS = "      TEST PASSED";

unsigned cyclic_hash16(string key);

int main() {
    vector<Car> cars;
    cars.push_back(Car("x101", 5, "super car"));
    cars.push_back(Car("x101", 12, "mega car"));
    cars.push_back(Car("x101", 4, "shack of cars"));
    cars.push_back(Car("challenger", 10, "mega car"));
    cars.push_back(Car("challenger", 5, "car world"));
    cars.push_back(Car("stratos", 7, "car world"));
    cars.push_back(Car("stratos", 15, "super car"));
    cars.push_back(Car("stratos", 8, "shack of cars"));
    cars.push_back(Car("challenger", 3, "car joint"));
    cars.push_back(Car("gt500", 3, "shack of cars"));
    cars.push_back(Car("miura", 28, "mega car"));
    cars.push_back(Car("gt500", 11, "super car"));
    
    Heap<Car> heap;
    HashTable<Car> ht(10, cyclic_hash16);
    Car c;
    Car d;

    vector<Car>::iterator itCar;
    for (itCar=cars.begin();itCar!=cars.end();itCar++)
        ht.insert(*itCar);

    cout << "ht Dump:" << endl;
    ht.dump();
    cout << endl;
    
    {   // readTop() exception test
        try {
            cout << "\n===readTop() on empty heap===" << endl;
            heap.readTop();
            cout << FAIL << endl;
        }
        catch (exception &ex) {
            cout << PASS << ": reading from empty heap throws exception" << endl;
        }

    }

    {   // removeTop() exception test
        try {
            cout << "\n===removeTop() on empty heap===" << endl;
            heap.removeTop();
            cout << FAIL << endl;
        }
        catch (exception &ex) {
            cout << PASS << ": removing from empty heap throws exception" << endl;
        }

    }

    {   // heap property test
        cout << "\n===Checks if heap property is maintained===" << endl;
        heap.insert(cars[0]);
        heap.insert(cars[1]);
        heap.insert(cars[2]);
        
        if (heap.readTop().priority() == cars[1].priority()) cout << PASS << ": heap maintains max heap property" << endl;
        else cout << FAIL << endl;
    }

    {   // copy constructor and assignment operator test
        cout << "\n===Copy constructor test===" << endl;
        HashTable<Car> ht2(ht);

        ht2.getNext("challenger", d);

        ht.getNext("challenger", c);
        ht2.getNext("challenger", d);

        if (c.priority() != d.priority()) cout << PASS << ": copy constructor is deep copy" << endl;
        else cout << FAIL << endl;

        cout << "\n===Assignment operator test===" << endl;
        ht = ht2;

        ht.getNext("x101", d);

        ht2.getNext("x101", c);
        ht.getNext("x101", d);
        if (c.priority() != d.priority()) cout << PASS << ": assignment operator is deep copy" << endl;
        else cout << FAIL << endl;
    }

    {   // empty copy constructor and assingment operator test
        HashTable<Car> ht2(ht);
        HashTable<Car> ht3(10, cyclic_hash16);
        HashTable<Car> ht4(ht3);
        ht2 = ht3;
        cout << "\n===Empty copy constructor test===" << endl;
        if (ht3.numEntries() == ht4.numEntries()) cout << PASS << ": copy constructor on empty hashtable" << endl;
        else cout << FAIL << endl;
        cout << "\n===Empty assignment operator test===" << endl;
        if (ht2.numEntries() == ht3.numEntries()) cout << PASS << ": assignment operator on empty hashtable" << endl;
        else cout << FAIL << endl;
    }

    {   // getNext() test
        HashTable<Car> ht2(ht);
        ht2.getNext("stratos", c);
        cout << "\n===getNext() test===" << endl;
        if (c.priority() == cars[6].priority() && c.key() == cars[6].key()) cout << PASS << ": getNext() returns correct value" << endl;
        else cout << FAIL << endl;

        cout << "\n===getNext() on nonexistent key===" << endl;
        ht2.getNext("miura", c);
        if (!ht2.getNext("miura", c)) cout << PASS << ": getNext() on an element that does not exist" << endl;
        else cout << FAIL << endl;
    }

    {   // Collision testing
        HashTable<Car> ht2(10, cyclic_hash16);

        cout << "===Inserts 'gt340', 'gt500', and '310z' which all hash to same index===" << endl;
        if (ht2.insert(Car("gt340", 5, "super car")) && 
            ht2.insert(Car("gt500", 2, "car world")) && 
            ht2.insert(Car("310z", 4, "mega car"))) cout << PASS << ": all keys inserted into heap" << endl;
        else cout << FAIL << endl;
    }
}   

unsigned cyclic_hash16(string key) {
  unsigned usize = 16;
  unsigned s = 5; // shift by 5
  unsigned h = 0;
  for ( int i = 0; i < key.length(); i++ ){
    h = (( h << s ) | ( h >> (usize - s) ));
    h += key[i];
    h = h & 0xffff;
  }
  return h;
}
