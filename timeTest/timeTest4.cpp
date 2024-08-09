#include <iostream>
#include <ctime>
#include <sys/time.h>

using namespace std;

int main(){
    // timeval gettimeofday는 마이크로초 단위까지 시간을 가져온다.
    // time(nullptr)는 초 단위까지 시간을 가져온다.
    // 즉 마이크로초 단위까지 시간이 필요한 경우 gettimeofday를 사용해야 한다.

    struct timeval tv;
    gettimeofday(&tv, nullptr);
    time_t t = tv.tv_sec;
    // time_t t = time(nullptr);
    struct tm* now_tm = localtime(&t);

    char buffer[20];
    char buffer1[20];
    char buffer2[20];
    char buffer3[20];

    strftime(buffer, sizeof(buffer1), "%Y%m%d%H%M%S", now_tm);
    sprintf(buffer1, "%s%03d", buffer, tv.tv_usec/1000);
    strftime(buffer2, sizeof(buffer2), "%Y%m%d", now_tm);
    strftime(buffer3, sizeof(buffer3), "%H%M%S", now_tm);

    cout << "buffer0: " << buffer << endl;
    cout << "buffer1: " << buffer1 << endl;
    cout << "buffer2: " << buffer2 << endl;
    cout << "buffer3: " << buffer3 << endl;

    return 0;
}