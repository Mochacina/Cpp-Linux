#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<string> split (string str, char separater){
    vector<string> list;
    string token;
    istringstream iss(str);

    while(getline(iss,token,separater)){
        list.push_back(token);
    }

    return list;
};