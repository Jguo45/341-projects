// CMSC 341 - Fall 2020 - Project 4
// heap.h
// Templated, vector-based heap implementation

// To work with Heap, the template class T must provide the following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) overloaded insertion operator
// To work with Heap *and* HashTable, it also needs:
//  (d) key function (string key())

#ifndef _HEAP_H
#define _HEAP_H

#include <iostream>
#include <vector>
#include <exception>
#include <utility>   // swap

using std::vector;
using std::endl;
using std::cout;
using std::swap;
using std::range_error;

// To work with Heap and HashTable, class T must provide the
// following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) key function (string key())
//  (d) overloaded insertion operator

class Grader;

template <class T>
class Heap {

  friend Grader;
  
 public:
  // Constructor
  Heap();

  // Inline functions: size, empty, used 
  unsigned size() const { return _heap.size() - 1 ; }
  bool empty() const { return _heap.size() <= 1 ; }
  bool used() const { return _used ; }

  // Main heap operations: insert, read, remove
  void insert(const T& object);
  T readTop() const;
  void removeTop();

  // Dump the entire heap
  void dump() const;

  // Root node always has index 1
  static const unsigned ROOT = 1;
  
 private:
  vector<T> _heap;   // Vector-based heap
  bool _used;        // Has the heap ever been used?  Needed for
		     // linear probing.

  // *********************************************
  // Private helper function declarations go here!
  // *********************************************
  void bubbleUp(int index);   // Recursively swaps with parent to maintain max heap property
  void bubbleDown(int index); // Recursively swaps with children to maintain max heap property
};

// ***************************************
// Templated function definitions go here!
// ***************************************

template <class T>
Heap<T>::Heap() {
  _heap = vector<T>(1); // Initializes the vector with only the 0 index
  _used = false;
}

template <class T>
void Heap<T>::insert(const T& object) {
  _used = true;
  if (empty()) {
    _heap.push_back(object);
    return;
  }

  _heap.push_back(object);  // Inserts object at the end of the vector
  bubbleUp(_heap.size() - 1); // Fixes max heap property
}

template <class T>
T Heap<T>::readTop() const {
  if (empty()) {
    throw range_error("Reading from empty heap.");
  }
  return _heap[ROOT];
}

template <class T>
void Heap<T>::removeTop() {
  if (empty()) {
    throw range_error("Removing from empty heap.");
  }

  _heap[ROOT] = _heap.back(); // Overwrites the root with the last element in the heap
  _heap.pop_back(); // Removes the last element in the heap
  bubbleDown(ROOT); // Fixes max heap property

  // Checks if heap is empty and updates _used
  if (empty()) {
    _used = false;
  }
}

template <class T>
void Heap<T>::dump() const {
  for (auto it = _heap.begin() + 1; it != _heap.end(); it++) {
    cout << *it << endl;
  }
}

template <class T>
void Heap<T>::bubbleUp(int index) {
  // Reached the beginning of the heap
  if (index <= ROOT) {
    return;
  }

  int parentIndex = index / 2;

  // Compares priority with parent to determine if swap is needed
  if (_heap[index].priority() > _heap[parentIndex].priority()) {
    swap(_heap[index], _heap[parentIndex]);
    bubbleUp(parentIndex);  
  }
}

template <class T>
void Heap<T>::bubbleDown(int index) {
  int leftIndex = index * 2;

  // Left index exists in heap
  if (leftIndex < _heap.size()) {
    int rightIndex = index * 2 + 1;

    // Right index exists in heap
    if (rightIndex < _heap.size()) {
      // Determines which child has the greater priority
      int swapIndex = _heap[leftIndex].priority() > _heap[rightIndex].priority() ? leftIndex : rightIndex;

      // Swaps if childs priority is greater
      if (_heap[index].priority() < _heap[swapIndex].priority()) {
        swap(_heap[index], _heap[swapIndex]);
        bubbleDown(swapIndex);
      }      
    }
    // Right child does not exist
    else {
      // Swaps if the left child has greater priority
      if (_heap[index].priority() < _heap[leftIndex].priority()) {
        swap(_heap[index], _heap[leftIndex]);
        bubbleDown(leftIndex);
      }
    }
  }
}

#endif
