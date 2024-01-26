#include "parseTest1.h"

using namespace std;

int main(){
    string input;
    getline(cin, input);

    vector<string> list = split(input, ',');

    for (string str : list){
        cout << str << endl;
    }
}

