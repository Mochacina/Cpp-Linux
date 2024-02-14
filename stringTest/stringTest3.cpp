#include <iostream>
#include <cstring>

using namespace std;

int main() {
    char atmCashP[4000+1];
    memset(atmCashP, 0x00, sizeof(atmCashP));

    char bufferQty[4+1] = "0000";
    char bufferAmt[9+1] = "000000000";

    char data[5+1] = {0,};

    int a = 5, b = 12, c = 90;

    int sum = a+b+c;

    sprintf(data, "%d", sum);

    cout << data << endl;

    sprintf(bufferQty, "%04d", sum);

    cout << bufferQty << endl;

    sprintf(bufferAmt, "%09d", sum*1000);

    cout << bufferAmt << endl;
}