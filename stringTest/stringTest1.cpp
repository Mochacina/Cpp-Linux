#include <iostream>
#include <cstring>

int main() {
    const int ORIGINAL_SIZE = 5;
    const int TARGET_SIZE = 4;
    char originalArr[ORIGINAL_SIZE + 1] = "Hello"; // ���� �迭
    char targetArr[TARGET_SIZE + 1]; // ��� �迭

    // ���� �迭���� �ڿ��� 4�ڸ��� �����Ͽ� ��� �迭�� �����մϴ�.
    strncpy(targetArr, originalArr + (ORIGINAL_SIZE - TARGET_SIZE), TARGET_SIZE);
    targetArr[TARGET_SIZE] = '\0'; // ���ڿ� ���� ��Ÿ���� �� ���� �߰�

    // ��� �迭�� ����� �����͸� ����մϴ�.
    std::cout << "��� �迭�� ����� ������: " << targetArr << std::endl;

    return 0;
}
