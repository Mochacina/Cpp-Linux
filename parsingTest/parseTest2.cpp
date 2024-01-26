//
//
// Error Code
//
//

#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

int main() {
    string input;
    getline(cin, input);
    const char* cstr = input.c_str();

    vector<string> tokens;
    char* token = strtok(const_cast<char*>(cstr), ",");

    cout << token << endl;

    while (token = strtok(nullptr, ",")) {
        tokens.push_back(token);
        //token = strtok(nullptr, ",");
        cout << token << endl;
    }

    delete[] cstr;

    // for (const std::string& t : tokens) {
    //     std::cout << t << std::endl;
    // }

    return 0;
}
