#include <iostream>
#include <cstring>

// 문자열을 동적으로 할당하고 그 주소를 반환하는 함수
void allocateString(char** str) {
    // 문자열 "Hello, World!"을 동적으로 할당
    char* newStr = new char[14];
    strcpy(newStr, "Hello, World!");
    *str = newStr;
}

int main() {
    char* myString = nullptr; // 문자열 포인터 초기화

    // 함수를 호출하여 문자열 할당
    allocateString(&myString);

    // 할당된 문자열 출력
    std::cout << "My String: " << myString << std::endl;

    // 할당된 메모리 해제
    delete[] myString;

    return 0;
}