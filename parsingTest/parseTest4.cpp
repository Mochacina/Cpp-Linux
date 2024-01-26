#include <iostream>
#include <string>
#include <regex>

using namespace std;

int main() {
    string input = "apple,banana,cherry";
    regex regex(",");
    sregex_token_iterator it(input.begin(), input.end(), regex, -1);
    sregex_token_iterator end;

    while (it != end) {
        cout << *it++ << endl;
    }

    return 0;
}