#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int main(){
    string input;
    getline(cin, input);
    istringstream is(input);
    string token;

    while(getline(is,token,',')){
        cout << "token: " << token << endl;
    }
}