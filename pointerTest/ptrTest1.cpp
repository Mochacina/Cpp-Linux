#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int main(){
    int n1 = 150;
    int* n2 = new int;
    cout << "nen int n2: " << n2 << endl;
    delete n2;
    n2 = &n1;

    cout << "n1: " << n1 << endl;
    cout << "&n1: " << &n1 << endl;
    cout << "n2: " << n2 << endl;
    cout << "*n2: " << *n2 << endl;

    return 0;
}