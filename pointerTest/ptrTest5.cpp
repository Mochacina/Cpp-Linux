#include <bits/stdc++.h>

int main(){
    int n = 0;
    std::cin >> n;
    //std::cin.tie(0);
    std::vector<std::string> l(n);
    for(int i=0; i<n; i++){
        std::cout << "Enter name: ";
        std::cin >> l[i];
    }
    for(std::string i : l){
        std::cout << i << std::endl;
    }

    return 0;
}