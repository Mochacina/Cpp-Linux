#include <iostream>
#include <chrono>
#include <thread>

int main() {
    // 마이크로초 단위로 sleep
    std::cout << "마이크로초 단위 대기 시작" << std::endl;
    std::this_thread::sleep_for(std::chrono::microseconds(100)); // 100 마이크로초 동안 대기
    std::cout << "마이크로초 단위 대기 종료" << std::endl;

    // 나노초 단위로 sleep
    std::cout << "나노초 단위 대기 시작" << std::endl;
    std::this_thread::sleep_for(std::chrono::nanoseconds(100)); // 100 나노초 동안 대기
    std::cout << "나노초 단위 대기 종료" << std::endl;

    return 0;
}