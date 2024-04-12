#include <bits/stdc++.h>

int main(){
    int* l = new int[10];
    for(int i=0; i<10; i++){
        l[i] = i;
    }
    for(int i : l){
        std::cout << i << std::endl;
    }

    delete[] l;
    return 0;
}