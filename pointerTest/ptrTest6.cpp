#include <iostream>
#include <cstdlib>

int main() {
    const char *str = "123abc";
    char *endptr;
    long num;

    std::cout << "str: " << str << std::endl;
    std::cout << "*str: " << *str << *(str+1) << *(str+2) << std::endl;
    std::cout << "&str: " << &str << std::endl;

    // ���ڿ��� long Ÿ������ ��ȯ
    num = strtol(str, &endptr, 10);

    std::cout << "endptr: " << endptr << std::endl;
    std::cout << "&endptr: " << &endptr << std::endl;

    // ��ȯ�� �� ���
    std::cout << "Converted number: " << num << std::endl;  // ���: 123

    // ��ȯ ���� ���ڿ� Ȯ��
    if (*endptr != '\0') {  // endptr�� ���ڿ��� ���� ����Ű�� �ʴ´ٸ�
        std::cout << "Conversion stopped at: " << endptr << std::endl;  // ���: abc
    }

    return 0;
}
