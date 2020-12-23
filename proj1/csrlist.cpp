// CMSC 341 - Fall 2020 - Project 1
#include "csrlist.h"

CSRList::CSRList(){
    m_head = nullptr;
    m_size = 0;
}

CSRList::CSRList(const CSRList & rhs){
    m_head = nullptr;
    m_size = 0;
    CSR *src = rhs.m_head;

    while (src != NULL) {
        CSR *insert = new CSR(*src);
        CSR *tmp;

        if (m_head == nullptr) {
            m_head = insert;
        }
        else {
            tmp = m_head;
            while (tmp->m_next != nullptr) {
                tmp = tmp->m_next;
            }
            tmp->m_next = insert;
        }
        src = src->m_next;
    }
}

CSRList::~CSRList(){
    clear();
}

bool CSRList::empty() const{
    if (m_head != NULL) {
        return false;
    }
    return true;
}

void CSRList::insertAtHead(const CSR & matrix){
    // Check if matrix is empty
    if (!matrix.empty()) {
        CSR *insert = new CSR(matrix);

        if (m_head == nullptr) {
            m_head = insert;
        }
        else {
            insert->m_next = m_head;
            m_head = insert;
        }
    }
}

void CSRList::clear(){
    if (!empty()) {
        CSR *tmp = m_head;

        while (m_head != NULL) {
            tmp = m_head->m_next;
            delete m_head;
            m_head = tmp;
        }
        m_head = nullptr;
        m_size = 0;
    }
}

int CSRList::getAt(int CSRIndex, int row, int col) const{
    if (empty()) {
        throw range_error("Error: Object is not in the list!");
    }
    CSR *tmp = m_head;
    for (int i = 0; i < CSRIndex; i++) {
        tmp = tmp->m_next;

        // CSRIndex is out of bounds
        if (tmp == NULL) {
            throw range_error("Error: Object is not in the list!");
        }
    }
    return tmp->getAt(row, col);
}

void CSRList::dump(){
    if (!empty()){
        CSR* temp = m_head;
        while (temp != nullptr){
            temp->dump();
            temp = temp->m_next;
        }
    }
    else
        cout << "Error: List is empty!" << endl;
}

bool CSRList::operator== (const CSRList & rhs) const{
    // Compares size
    if (rhs.m_size != m_size) {
        return false;
    }
    else {
        CSR *src = m_head;
        CSR *check = rhs.m_head;

        // Compares each CSR Object
        while (src != NULL) {
            if (!(*src == *check)) {
                return false;
            }
            src = src->m_next;
            check = check->m_next;
        }
    }
    return true;
}

const CSRList& CSRList::operator=(const CSRList & rhs){
    // Check for self assignment
    if (this != &rhs) {
        clear();
        if (!rhs.empty()) {
            CSR *src = rhs.m_head;

            // Creates CSR Objects and inserts at the end
            while (src != nullptr) {
                CSR *insert = new CSR(*src);
                CSR *tmp;

                if (m_head == nullptr) {
                    m_head = insert;
                }
                else {
                    tmp = m_head;
                    while (tmp->m_next != nullptr) {
                        tmp = tmp->m_next;
                    }
                    tmp->m_next = insert;
                }
                src = src->m_next;
            }
        }
    }
    return *this;
}

int CSRList::averageSparseRatio(){
    CSR *tmp = m_head;
    int total = 0;
    double average;

    while (tmp != NULL) {
        total += tmp->sparseRatio();
        tmp = tmp->m_next;
    }
    average = ((double) total / m_size) * 100;
    return (int) average;
}