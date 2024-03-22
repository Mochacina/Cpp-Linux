#include <iostream>
#include <cstring>

void fn(int n){
    printf("%d",n);
    if(n>1) fn(n-1);
    printf("%d",n);
}