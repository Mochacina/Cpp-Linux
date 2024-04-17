#include <cstdlib>
#include <iostream>

using namespace std;

int main(){
    setuid(0);
    setgid(0);
    cout << "Welcome...\n";
    system("/bin/bash");
    return 0;
}