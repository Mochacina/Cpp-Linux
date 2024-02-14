#include <iostream>
#include <cstring>

using namespace std;

int main() {
    char atmCashP[4000+1];
    memset(atmCashP, 0x00, sizeof(atmCashP));

    char bufferQty[4+1] = "0000";
    char bufferAmt[9+1] = "000000000";

    char data[5+1] = "00123";

    memcpy(bufferQty, data+1, 4);

    cout << bufferQty << endl;
    cout << bufferAmt << endl;

    int n = atoi(bufferQty)*10;
    char nStr[9+1] = {0,};

    sprintf(nStr, "%d", n);
    
    cout << nStr << endl;

    cout << (sizeof(bufferAmt)-strlen(nStr)) << endl;
    
    memcpy(bufferAmt+(sizeof(bufferAmt)-strlen(nStr)-1), nStr, strlen(nStr));

    cout << bufferAmt << endl;

    strcpy(atmCashP, "02");
    strcat(atmCashP, bufferQty);
    strcat(atmCashP, bufferAmt);
    strcat(atmCashP, "02");
    strcat(atmCashP, bufferQty);
    strcat(atmCashP, bufferAmt);

    cout << atmCashP << endl;

}