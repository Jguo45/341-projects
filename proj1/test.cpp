#include "csr.h"

int main()
{
    try{
        CSR aCSR;
        int array1[] = {10,20,0,0,0,0,0,30,0,40,0,0,0,0,50,60,70,0,0,0,0,0,0,80};
        // int array2[] = {10,20,0,0,0,0,0,30,0,40,0,0,0,0,50,60,70,0,0,0,0,0,0,81};
        aCSR.compress(4,6,array1,24);//initialize object aCSR
        // aCSR.dump();
        CSR bCSR(aCSR);
        bCSR.dump();
        // cout << aCSR.getAt(0, 0) << endl;
    }
    catch (exception &e){
        cout << e.what() << endl;
    }
    return 0;
}