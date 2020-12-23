// CMSC 341 - Fall 2020 - Project 4
// hash.h

// Templated, hash table implementation.  Each buckets is a heap.  A
// bucket contains objects with the same key values stored as a
// max-heap based on priority.  Collisions are resolved by linear
// probing.

// To work with Heap and HashTable, the template class T must provide
// the following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) key function (string key())
//  (d) overloaded insertion operator

#ifndef _HASH_H
#define _HASH_H

#include <string>
#include "heap.h"

using std::string;

// Hash function typedef.  The hash function must return an 'unsigned
// int' value.  Reduction mod N is the responsiblity of the caller,
// not the hash function.
typedef unsigned (*hash_fn)(string);

class Grader;

template <class T>
class HashTable {

  friend Grader;
  
 public:
  // Constructor.  Requires table size and hash function.
  HashTable(unsigned size, hash_fn hash);

  // Destructor, copy, and assignment
  ~HashTable();
  HashTable(const HashTable<T>& ht);
  const HashTable<T>& operator=(const HashTable<T>& ht);

  // In-line functions
  
  // Table size; set by constructor
  unsigned tableSize() const { return _N; }
  // Number of entries in the table
  unsigned numEntries() const { return _n; }
  // Load factor
  float lambda() const { return ((float) _n) / _N; }

  // Main hash table functions
  
  // insert returns 'true' if successful; 'false' otherwise
  bool insert(const T& object);
  // getNext retrieves **and removes** the highest priority order of
  // type indicated by key.  It returns 'true' if successful; 'false'
  // otherwise.
  bool getNext(string key, T& obj);

  // Dump the entire hash table
  void dump() const;
  
 private:
  unsigned _N;       // hash table size
  unsigned _n;       // current number of entries
  hash_fn _hash;     // hash function
  Heap<T> *_table;   // array of heaps

  // ***********************************************
  // Private helper function declarations go here! *
  // ***********************************************
  
};

// *****************************************
// Templated function definitions go here! *
// *****************************************

template <class T>
HashTable<T>::HashTable(unsigned size, hash_fn hash) {
  _table = new Heap<T>[size]{Heap<T>()};
  _hash = hash;
  _N = size;
  _n = 0;
}

template <class T>
HashTable<T>::~HashTable() {
  delete[] _table;
}

template <class T>
HashTable<T>::HashTable(const HashTable<T>& ht) {
  _hash = ht._hash;
  _N = ht._N;
  _n = ht._n;

  _table = new Heap<T>[_N]{Heap<T>()};

  // Copies each heap into array
  for (int i = 0; i < _N; i++) {
    _table[i] = ht._table[i];
  }
}

template <class T>
const HashTable<T>& HashTable<T>::operator=(const HashTable<T>& ht) {
  if (this != &ht) {
    delete[] _table;  // Clears existing table
    _hash = ht._hash;
    _N = ht._N;
    _n = ht._n;
    _table = new Heap<T>[_N]{Heap<T>()};

    // Copies each heap into array
    for (int i = 0; i < _N; i++) {
      _table[i] = ht._table[i];
    }
  }

  return *this;
}

template <class T>
bool HashTable<T>::insert(const T& object) {
  // Checks if there is space in the array
  if (_n < _N) {
    int index = _hash(object.key()) % _N;

    // Linear probing to find an empty heap
    while (_table[index].used()) {
      // Checks if key already exists 
      if (_table[index].readTop().key() == object.key()) {
        _n--; // Does not increment size if key already exists
        break;
      }

      // Increments index within range of the array
      if (index < _N - 1) {
        index++;
      }
      else if (index == _N - 1) {
        index = 0;  // Loops to the front
      }

      if (index == (_hash(object.key()) % _N)) {
        return false; // No empty bucket found in array
      }
    }

    // Inserts object into the heap at index
    _table[index].insert(object);
    _n++; // Increments size
    return true;  // Insert successfully
  }
  return false; // Insert failed
}

template <class T>
bool HashTable<T>::getNext(string key, T& obj) {
  int index = _hash(key) % _N;

  // Linear probing to find key
  while (_table[index].used()) {
    // Checks if key is found
    if (_table[index].readTop().key() == key) {
      break;
    }

    // Increments index within range of array
    if (index < _N - 1) {
      index++;
    }
    else if (index == _N - 1) {
      index = 0;  // Loops to the front
    }

    // Key does not exist in the array
    if (index == (_hash(key) % _N)) {
      return false;
    }
  }
  // Checks if the heap is empty
  if (!_table[index].empty()) {
    obj = _table[index].readTop();  // Stores the highest priority item in obj
    _table[index].removeTop();
    return true;  // Key found successfully
  }
  return false; // Key not found
}

template <class T>
void HashTable<T>::dump() const {
  for (int i = 0; i < _N; i++) {
    cout << "[" << i << "]:" << endl;
    _table[i].dump();
  }
}

#endif
