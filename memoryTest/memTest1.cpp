#include <bits/stdc++.h>

using namespace std;

int main (){
    int* intArray = new int[10];
    int* intArray2 = (int*)malloc(sizeof(int)*10);

    cout << sizeof(intArray) << endl;
    cout << sizeof(intArray2) << endl;

    delete[] intArray;
    free(intArray2);

    return 0;
}