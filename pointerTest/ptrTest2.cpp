#include <iostream>
#include <cstring>

// ���ڿ��� �������� �Ҵ��ϰ� �� �ּҸ� ��ȯ�ϴ� �Լ�
void allocateString(char** str) {
    // ���ڿ� "Hello, World!"�� �������� �Ҵ�
    char* newStr = new char[14];
    strcpy(newStr, "Hello, World!");
    *str = newStr;
}

int main() {
    char* myString = nullptr; // ���ڿ� ������ �ʱ�ȭ

    // �Լ��� ȣ���Ͽ� ���ڿ� �Ҵ�
    allocateString(&myString);

    // �Ҵ�� ���ڿ� ���
    std::cout << "My String: " << myString << std::endl;

    // �Ҵ�� �޸� ����
    delete[] myString;

    return 0;
}