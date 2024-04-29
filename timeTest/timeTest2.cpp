#include <iostream>
#include <sys/time.h>
#include <ctime>

int main() {
    struct timeval tv;
    gettimeofday(&tv, NULL);

    // �ð��� std::time_t�� ��ȯ
    std::time_t now = tv.tv_sec;
    struct tm* ptm = localtime(&now);

    // �ð��� �и������� ���
    std::cout << (ptm->tm_year + 1900) << '-' 
              << (ptm->tm_mon + 1) << '-' 
              << ptm->tm_mday << ' ' 
              << ptm->tm_hour << ':' 
              << ptm->tm_min << ':' 
              << ptm->tm_sec << '.' 
              << (tv.tv_usec / 1000) << std::endl;  // ����ũ���ʸ� �и��ʷ� ��ȯ

    return 0;
}
