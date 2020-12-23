// CMSC 341 - Fall 2020 - Project 1
#include "csr.h"

CSR::CSR(){
    m_values = nullptr;
    m_col_index = nullptr;
    m_row_index = nullptr;
    m_next = nullptr;
    m_nonzeros = 0;
    m_m = 0;
    m_n = 0;
}

CSR::~CSR(){
    clear();
}

CSR::CSR(const CSR & rhs){
    m_values = new int[rhs.m_nonzeros];
    m_col_index = new int[rhs.m_nonzeros];
    m_row_index = new int[rhs.m_m + 1];
    m_nonzeros = rhs.m_nonzeros;
    m_m = rhs.m_m;
    m_n = rhs.m_n;
    m_next = nullptr;
    
    // Copies m_values and m_col_index values
    for (int i = 0; i < m_nonzeros; i++) {
        m_values[i] = rhs.m_values[i];
        m_col_index[i] = rhs.m_col_index[i];
    }
    // Copies m_row_index values
    for (int i = 0; i < m_m + 1; i++) {
        m_row_index[i] = rhs.m_row_index[i];
    }
}

void CSR::dump(){
    cout << endl;
    if (!empty()){
        for (int i=0;i<m_nonzeros;i++)
            cout << m_values[i] << " ";
        cout << endl;
        for (int i=0;i<m_nonzeros;i++)
            cout << m_col_index[i] << " ";
        cout << endl;
        for (int i=0;i<m_m+1;i++)
            cout << m_row_index[i] << " ";
    }
    else
        cout << "The object is empty!";
    cout << endl;
}

void CSR::clear(){
    // Deallocates arrays
    delete[] m_values;
    delete[] m_col_index;
    delete[] m_row_index;
    m_values = nullptr;
    m_col_index = nullptr;
    m_row_index = nullptr;
    m_m = 0;
    m_n = 0;
}

bool CSR::empty() const{
    if (m_m == 0 && m_n == 0) {
        return true;
    }
    return false;
}

void CSR::compress(int m, int n, int array[], int arraySize){
    int range = m * n < arraySize ? m * n : arraySize;
    int row = 0;
    int col = 0;
    int count = 0;
    m_nonzeros = 0;
    m_m = m;
    m_n = n;

    // Determines number of nonzeros
    for (int i = 0; i < range; i++) {
        if (array[i] != 0) {
            m_nonzeros++;
        }
    }

    if (m_nonzeros > 0) {
        // Initializes arrays
        m_values = new int[m_nonzeros];
        m_col_index = new int[m_nonzeros];
        m_row_index = new int[m_m + 1];
        m_row_index[0] = 0;

        // Loops through smallest size between m * n and arraySize
        for (int i = 0; i < range; i++) {
            // Resets col index
            if (col == m_n) {
                col = 0;
                row++;
                m_row_index[row] = count;
            }
            if (array[i] != 0) {
                m_values[count] = array[i];
                m_col_index[count] = col;
                count++;
            }
            col++;
        }
        m_row_index[m_m] = count;
    }
}

int CSR::getAt(int row, int  col) const{
    // Indexes out of bounds
    if ((row >= m_m || row < 0) || (col >= m_n || col < 0)) {
        throw runtime_error("Error: Invalid index.");
    }
    int row_start = m_row_index[row];
    int row_end = m_row_index[row + 1];

    for (int i = row_start; i < row_end; i++) {
        if (m_col_index[i] == col) {
            return m_values[i];
        }
    }
    return 0;
} 

bool CSR::operator==(const CSR & rhs) const{
    // Checks for identical matrix size and number of nonzeros
    if (rhs.m_m == m_m && rhs.m_n == m_n && rhs.m_nonzeros == m_nonzeros) {
        // Compares m_values and m_col_index
        for (int i = 0; i < m_nonzeros; i++) {
            if (rhs.m_values[i] != m_values[i]) {
                return false;
            }
            if (rhs.m_col_index[i] != m_col_index[i]) {
                return false;
            }
        }
        // Compares m_row_index
        for (int i = 0; i < m_m; i++) {
            if (rhs.m_row_index[i] != m_row_index[i]) {
                return false;
            }
        }
    }
    else {
        return false;
    }
    return true;
}

int CSR::sparseRatio(){
    int total = m_m * m_n;
    double ratio = ((double) (total - m_nonzeros) / total) * 100;
    return (int) ratio;
}