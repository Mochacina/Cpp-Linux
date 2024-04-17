#include <bits/stdc++.h>

using namespace std;

typedef struct memoryTest1
{
    /* data */
    string name;
    int number1;
    int number2;
    int vecSize = 10;
    vector<string> vec = vector<string>(vecSize);
};


int main(){
    memoryTest1* mem1 = new memoryTest1;
    mem1->name = "Tester";
    mem1->number1 = 1;
    mem1->number2 = 1;
    for (int i = 0; i < mem1->vecSize; i++){
        mem1->vec[i] = "Test"+to_string(i);
    }
    cout << mem1->name << " " << mem1->number1 << " " << mem1->number2 << "\n";
    
    for (const string &word : mem1->vec){
        cout << word << "\n";
    }

    delete mem1;
    return 0;
}