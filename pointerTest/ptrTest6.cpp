#include <iostream>
#include <cstdlib>

int main() {
    const char *str = "123abc";
    char *endptr;
    long num;

    std::cout << "str: " << str << std::endl;
    std::cout << "*str: " << *str << *(str+1) << *(str+2) << std::endl;
    std::cout << "&str: " << &str << std::endl;

    // 문자열을 long 타입으로 변환
    num = strtol(str, &endptr, 10);

    std::cout << "endptr: " << endptr << std::endl;
    std::cout << "&endptr: " << &endptr << std::endl;

    // 변환된 값 출력
    std::cout << "Converted number: " << num << std::endl;  // 출력: 123

    // 변환 후의 문자열 확인
    if (*endptr != '\0') {  // endptr이 문자열의 끝을 가리키지 않는다면
        std::cout << "Conversion stopped at: " << endptr << std::endl;  // 출력: abc
    }

    return 0;
}
