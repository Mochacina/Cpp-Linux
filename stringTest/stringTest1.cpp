#include <iostream>
#include <cstring>

int main() {
    const int ORIGINAL_SIZE = 5;
    const int TARGET_SIZE = 4;
    char originalArr[ORIGINAL_SIZE + 1] = "Hello"; // 원본 배열
    char targetArr[TARGET_SIZE + 1]; // 대상 배열

    // 원본 배열에서 뒤에서 4자리를 복사하여 대상 배열에 저장합니다.
    strncpy(targetArr, originalArr + (ORIGINAL_SIZE - TARGET_SIZE), TARGET_SIZE);
    targetArr[TARGET_SIZE] = '\0'; // 문자열 끝을 나타내는 널 문자 추가

    // 대상 배열에 저장된 데이터를 출력합니다.
    std::cout << "대상 배열에 저장된 데이터: " << targetArr << std::endl;

    return 0;
}
