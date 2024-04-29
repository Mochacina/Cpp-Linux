#include <iostream>
#include <sys/time.h>
#include <ctime>
#include <iomanip>  // std::setw, std::setfill

int main() {
    struct timeval tv;
    gettimeofday(&tv, NULL);  // ���� �ð��� �ʿ� ����ũ���ʷ� ������

    struct tm* timeinfo;
    char buffer[80];

    time_t now = tv.tv_sec;  // �� ���� �ð�
    timeinfo = localtime(&now);  // ���� �ð����� ��ȯ

    // YYYYMMDDHHMISS �������� ����
    strftime(buffer, sizeof(buffer), "%Y%m%d%H%M%S", timeinfo);

    std::cout << buffer << std::setw(3) << std::setfill('0') << (tv.tv_usec / 1000) << std::endl;  // �и������� �߰�

    char buffer2[17+1];
    sprintf(buffer2, "%s%03d", buffer, (int)(tv.tv_usec / 1000));

    std::cout << buffer2 << std::endl;

    return 0;
}