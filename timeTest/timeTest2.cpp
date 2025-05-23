#include <iostream>
#include <sys/time.h>
#include <ctime>

int main() {
    struct timeval tv;
    gettimeofday(&tv, NULL);

    // 시간을 std::time_t로 변환
    std::time_t now = tv.tv_sec;
    struct tm* ptm = localtime(&now);

    // 시간과 밀리세컨드 출력
    std::cout << (ptm->tm_year + 1900) << '-' 
              << (ptm->tm_mon + 1) << '-' 
              << ptm->tm_mday << ' ' 
              << ptm->tm_hour << ':' 
              << ptm->tm_min << ':' 
              << ptm->tm_sec << '.' 
              << (tv.tv_usec / 1000) << std::endl;  // 마이크로초를 밀리초로 변환

    return 0;
}
