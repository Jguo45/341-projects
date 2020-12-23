#include "csrlist.h"

bool testEquality(CSR& a, CSR& b);
bool testEquality(CSRList& a, CSRList& b);

int main() {
    try {
        int array1[] = {10,20,0,0,0,0,0,30,0,40,0,0,0,0,50,60,70,0,0,0,0,0,0,80};
        int array2[] = {0,0,0,0,100,200,0,0,300};
        int array3[] = {2,0,4,5};
        CSR aCSR;
        CSR bCSR;
        CSR eCSR;

        cout << "===Empty CSR Equality===" << endl; // Pass
        if (testEquality(aCSR, bCSR)) cout << "passed" << endl;
        else cout << "failed" << endl;

        aCSR.compress(4,6,array1,24);
        bCSR.compress(3,3,array2,9);

        cout << endl << "===CSR Equality===" << endl; // Fail
        if (testEquality(aCSR, bCSR)) cout << "passed" << endl;
        else cout << "failed" << endl;

        CSR cCSR(bCSR);
        CSR dCSR(cCSR);

        cout << endl << "===Test clear()===" << endl; // Pass
        dCSR.clear();
        if (dCSR.empty()) cout << "passed" << endl;
        else cout << "failed" << endl;

        cout << endl << "===Test 0x0 Matrix===" << endl; // Pass
        aCSR.compress(0,0,array1,24); // Empty Matrix
        if (aCSR.empty()) cout << "passed" << endl;
        else cout << "failed" << endl;

        aCSR.clear();
        bCSR.clear();
        cCSR.clear();
        dCSR.clear();
        
        aCSR.compress(4,6,array1,24);
        bCSR.compress(4,6,array1,24);
        cCSR.compress(3,3,array2,9);
        dCSR.compress(3,3,array2,9);
        eCSR.compress(2,2,array3,4);

        CSRList aCSRList;
        CSRList bCSRList;

        cout << endl << "===Empty CSRList Equality===" << endl; // Pass
        if (testEquality(aCSRList, bCSRList)) cout << "passed" << endl;
        else cout << "failed" << endl;

        aCSRList.insertAtHead(aCSR);
        aCSRList.insertAtHead(cCSR);
        bCSRList.insertAtHead(dCSR);
        bCSRList.insertAtHead(bCSR);
        CSRList cCSRList;
        cCSRList = aCSRList;

        cout << endl << "===Test CSRList Assignment Operator===" << endl; // Pass
        if (testEquality(aCSRList, cCSRList)) cout << "passed" << endl;
        else cout << "failed" << endl;

        aCSRList.insertAtHead(eCSR);
        cout << endl << "===Test CSRList Deep Copy===" << endl; // Fail
        if (testEquality(aCSRList, cCSRList)) cout << "passed" << endl;
        else cout << "failed" << endl;

        aCSRList.clear();
        cout << endl << "===Test CSRList clear()===" << endl; // Pass
        if (aCSRList.empty()) cout << "passed" << endl;
        else cout << "failed" << endl;

        cout << endl << "===Test getAt() for 0 value===" << endl;
        cout << "cCSR(0,0): " << cCSR.getAt(0,0) << endl;

        // cout << "===Test Out of CSRList Index===" << endl; // Throws range_error exception
        // cout << "bCSRList(10,0,0): " << bCSRList.getAt(10,0,0) << endl;

        cout << endl << "=== Test CSR Index Out of Bounds===" << endl; // Throws runtime_error exception
        cout << "bCSRList(1,20,20): " << bCSRList.getAt(0,20,20) << endl;
    }
    catch (exception &e) {
        cout << e.what() << endl;
    }
}

bool testEquality(CSR& a, CSR& b){
    return (a == b);
}
bool testEquality(CSRList& a, CSRList& b){
    return (a == b);
}