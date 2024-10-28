#include <bits/stdc++.h>

using namespace std;

string rtrim (string& str) {
    size_t end = str.find_last_not_of(' ');
    cout << "found end: " << end << endl;
    if (end == string::npos) {
        return "";
    } else {
        return str.substr(0,end+1);
    }

}

int main() {
    string test = "test    ";
    string test2 = rtrim(test);
    cout << test2 << endl;

}