#include <iostream>

using namespace std;

int main (){
    int a [2][3]  = { {1,2,3}, {4,5,6} };
    printf("%d \n", sizeof(a));
    printf("%d \n", sizeof(&a));
    printf("%d \n", sizeof(a[0]));
    printf("%d \n", sizeof(*a));
    printf("%d \n", sizeof(a[0][0]));
    printf("%d \n", sizeof(a[0]+1));
    printf("%d \n", sizeof(a[0][0]+1));

    return 0;
}