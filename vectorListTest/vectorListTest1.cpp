#include <bits/stdc++.h>

int main (){
    std::vector<std::string> vecTest;

    vecTest.push_back("Test1");
    vecTest.push_back("Test2");
    vecTest.push_back("Test3");

    for (std::string _str : vecTest){
        std::cout << _str << std::endl;
    }

    return 0;
}