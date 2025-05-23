//timeTest.hpp

#include <bits/stdc++.h>
#include <iostream>
#include <ctime>
#include <sys/time.h>

struct timeTest {
    struct timeval tv;
    time_t t;
    struct tm* now_tm;
    char timeYmd[8+1];
    char timeHMS[6+1];
    char timeYmdHms3[17+1];
};

auto getTime(){
    timeTest T = {};

    gettimeofday(&T.tv, nullptr);
    T.t = T.tv.tv_sec;
    T.now_tm = localtime(&T.t);

    strftime(T.timeYmd, sizeof(T.timeYmd), "%Y%m%d", T.now_tm);
    strftime(T.timeHMS, sizeof(T.timeHMS), "%H%M%S", T.now_tm);
    sprintf(T.timeYmdHms3, "%s%s%03ld", T.timeYmd, T.timeHMS);

    return T;
}