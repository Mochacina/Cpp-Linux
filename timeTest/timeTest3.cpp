#include <iostream>
#include <sys/time.h>
#include <ctime>
#include <iomanip>  // std::setw, std::setfill

int main() {
    struct timeval tv;
    gettimeofday(&tv, NULL);  // 현재 시간을 초와 마이크로초로 가져옴

    struct tm* timeinfo;
    char buffer[80];

    time_t now = tv.tv_sec;  // 초 단위 시간
    timeinfo = localtime(&now);  // 현지 시간으로 변환

    // YYYYMMDDHHMISS 형식으로 포맷
    strftime(buffer, sizeof(buffer), "%Y%m%d%H%M%S", timeinfo);

    std::cout << buffer << std::setw(3) << std::setfill('0') << (tv.tv_usec / 1000) << std::endl;  // 밀리세컨드 추가

    return 0;
}