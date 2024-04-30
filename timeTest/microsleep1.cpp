#include <iostream>
#include <chrono>
#include <thread>

int main() {
    // ����ũ���� ������ sleep
    std::cout << "����ũ���� ���� ��� ����" << std::endl;
    std::this_thread::sleep_for(std::chrono::microseconds(100)); // 100 ����ũ���� ���� ���
    std::cout << "����ũ���� ���� ��� ����" << std::endl;

    // ������ ������ sleep
    std::cout << "������ ���� ��� ����" << std::endl;
    std::this_thread::sleep_for(std::chrono::nanoseconds(100)); // 100 ������ ���� ���
    std::cout << "������ ���� ��� ����" << std::endl;

    return 0;
}