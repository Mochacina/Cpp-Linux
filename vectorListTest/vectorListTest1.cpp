#include <bits/stdc++.h>

int main (){
    std::vector<std::string> vecTest;

    vecTest.push_back("Test1");
    vecTest.push_back("Test2");
    vecTest.push_back("Test3");

    for (std::string _str : vecTest){
        std::cout << _str << std::endl;
    }

    for (auto it = vecTest.begin(); it != vecTest.end(); it++){
        std::cout << *it << std::endl;
    }

    return 0;
}