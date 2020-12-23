// CMSC 341 - Fall 2020 - Project 3
// PQueue: an ER triage queue using a skew heap and function pointers

#include "pqueue.h"
using namespace std;
using std::cout;
using std::endl;
using std::domain_error;

PQueue::PQueue(prifn_t priFn) {
  priority = priFn;
  _heap = nullptr;
  _size = 0;
}

PQueue::~PQueue() {
  clear();
}

PQueue::PQueue(const PQueue& rhs) {
  _heap = nullptr;
  priority = rhs.priority;
  _size = rhs._size;

  clear(); // Clears any existing queue
  _heap = copy(rhs._heap);  // Creates a deep copy queue from rhs into this
}


PQueue& PQueue::operator=(const PQueue& rhs) {
  // Checks for self assignment
  if (this != &rhs) {
    priority = rhs.priority;
    _size = rhs._size;
    clear();  // Clears any existing queue
    _heap = copy(rhs._heap);  // Creates a deep copy queue from rhs into this
  }
  return *this;
}

void PQueue::insertPatient(const Patient& input) {
  Node *patient = new Node(input);  // Allocates memory for a new patient
  
  // Checks if queue is empty
  if (_size == 0) {
    _heap = patient;
  }
  // Merges patient into queue based on priority
  else {
    merge(_heap, patient);
  }

  _size++;  // Increases size of the queue
}

Patient PQueue::getNextPatient() {
  // getNextPatient() called on empty queue
  if (!_heap) {
    throw domain_error("Queue is empty");
  }

  Patient tmp = _heap->_patient;  // Stores value of patient to be returned

  // Stores children of _heap
  Node *root1 = _heap->_left;
  Node *root2 = _heap->_right;
  // Deletes the highest priority node
  delete _heap;

  _heap = root1;
  merge(_heap, root2); // Merges the children of the deleted node
  _size--;  // Decreases the size of the queue

  return tmp;
}


void PQueue::mergeWithQueue(PQueue& rhs) {
  // Priorities do not match
  if (priority != rhs.priority) {
    throw domain_error("Mismatch priorities");
  }
  // Base case : rhs no longer has any patients
  if (!rhs._heap) {
    return;
  }

  // Allocates memeory for the new patient from rhs
  Node *tmp = new Node(rhs.getNextPatient());
  _size++;  // Update size of queue

  _heap = merge(_heap, tmp);  // Merge new patient into existing queue
  mergeWithQueue(rhs);  // Recursive call until rhs no longer has any patients
}

void PQueue::clear() {
  clear(_heap); // Calls clear() on entire queue
  _heap = nullptr;
}

int PQueue::numPatients() const {
  return _size;
}

void PQueue::printPatientQueue() const {
  cout << "Contents of the patient queue: " << endl;
  printPatientQueue(_heap); // Calls printPatientQueue() on entire queue
}

prifn_t PQueue::getPriorityFn() const {
  return priority;
}

void PQueue::setPriorityFn(prifn_t priFn) {
  PQueue tmp = PQueue(*this); // Creates temporary queue from this using copy constructor

  _size = 0;  // Resets size
  priority = priFn; // Updates priority
  clear();  // Clears existing queue
  // Reinsert all the patients back into the queue with the new priority function
  while (tmp._heap) {
    insertPatient(tmp.getNextPatient());
  }
}

void PQueue::dump() const {
  dump(_heap);  // Calls dump() on entire queue
  cout << endl;
}

ostream& operator<<(ostream& sout, const Patient& patient) {
  sout << "Patient: " << patient.getPatient() << ", triage: " << patient.getTriage()
       << ", temperature: " << patient.getTemperature() << ", oxygen: " << patient.getOxygen() << ", RR: "
       << patient.getRR() << ", HR: " << patient.getHR() << ", BP: " << patient.getBP();
  return sout;
}

ostream& operator<<(ostream& sout, const Node& node) {
  sout << node.getPatient();
  return sout;
}

/////////////////////////////////////////////////////////////////////////////////

void PQueue::clear(Node *node) {
  // Checks of node exists
  if (node == nullptr) {
    return;
  }

  // Recursively clears the left and right trees
  clear(node->_left);
  clear(node->_right);

  // Deallocates memory for node
  delete node;
}

Node* PQueue::merge(Node* root1, Node* root2) {
  // Base cases : returns other root if this one does not exist
  if (!root1) {
    return root2;
  }
  else if (!root2) {
    return root1;
  }

  // Checks if root1 has the higher priority (lower number)
  if (priority(root1->_patient) > priority(root2->_patient)) {
    // Updates _heap if needed
    if (root1 == _heap) {
      _heap = root2;
    }
    // Recursive call to ensure root1 has the greater priority
    return merge(root2, root1);
  }

  // Swaps children
  Node *tmp = root1->_left;
  root1->_left = root1->_right;
  root1->_right = tmp;

  // Inserts on the left
  root1->_left = merge(root1->_left, root2);
  return root1;
}

void PQueue::printPatientQueue(Node *node) const {
  if (!node) {
    return;
  }

  // Preorder traversal to print the patients in the queue
  cout << "[" << priority(node->_patient) << "] " << node->_patient << endl;
  printPatientQueue(node->_left);
  printPatientQueue(node->_right);
}

void PQueue::dump(Node *node) const {
  // Checks if node exists
  if (node) {
    // Displays node data using inorder traversal
    cout << "(";
    dump(node->_left);
    cout << priority(node->_patient) << ":" << node->_patient.getPatient();
    dump(node->_right);
    cout << ")";
  }
}

Node* PQueue::copy(Node *node) {
  // Checks if node exists
  if (!node) {
    return nullptr;
  }

  // Preorder traversal to correctly set the children of node
  Node *tmp = new Node(node->_patient);
  tmp->_left = copy(node->_left);
  tmp->_right = copy(node->_right);

  return tmp;
}