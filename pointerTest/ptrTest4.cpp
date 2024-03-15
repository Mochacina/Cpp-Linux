#include <iostream>
#include <memory>

int n = 10;
void show(){
    std::cout << "n = " << n << std::endl;
    std::cout << "*n = " << &n << std::endl;
    
}

int main() {
    int n = 5;
    show();
    printf("n = %d\n", n);
    printf("*n = %d\n", &n);

    return 0;
}