#include <iostream>
#include <iomanip>
#include <ctime>

// 8자리 날짜와 6자리 시간을 std::tm 구조체로 변환
std::tm parse_datetime(int yyyymmdd, int hhmmss) {
    std::tm time_struct = {};
    time_struct.tm_year = (yyyymmdd / 10000) - 1900; // 연도 (tm_year는 1900 기준)
    time_struct.tm_mon = ((yyyymmdd / 100) % 100) - 1; // 월 (0부터 시작)
    time_struct.tm_mday = yyyymmdd % 100; // 일
    time_struct.tm_hour = hhmmss / 10000; // 시
    time_struct.tm_min = (hhmmss / 100) % 100; // 분
    time_struct.tm_sec = hhmmss % 100; // 초
    return time_struct;
}

// std::tm 구조체를 날짜(8자리)와 시간(6자리)으로 변환
void tm_to_datetime(const std::tm& time_struct, int &yyyymmdd, int &hhmmss) {
    yyyymmdd = (time_struct.tm_year + 1900) * 10000 + (time_struct.tm_mon + 1) * 100 + time_struct.tm_mday;
    hhmmss = time_struct.tm_hour * 10000 + time_struct.tm_min * 100 + time_struct.tm_sec;
}

// 시간을 계산하고 출력하는 함수
void calculate_datetime(int yyyymmdd, int hhmmss, int adjustment) {
    // 8자리 날짜와 6자리 시간을 std::tm 구조체로 변환
    std::tm time_struct = parse_datetime(yyyymmdd, hhmmss);

    // std::tm을 time_t로 변환
    time_t time_in_seconds = mktime(&time_struct);

    if (time_in_seconds == -1) {
        std::cerr << "Error: invalid time conversion." << std::endl;
        return;
    }

    // 초 단위로 조정 (+1초 또는 -1초)
    time_in_seconds += adjustment;

    // 조정된 초를 다시 std::tm으로 변환
    std::tm* adjusted_time = localtime(&time_in_seconds);

    // 조정된 날짜와 시간 출력
    int new_yyyymmdd, new_hhmmss;
    tm_to_datetime(*adjusted_time, new_yyyymmdd, new_hhmmss);

    std::cout << "Adjusted datetime: "
              << new_yyyymmdd << " "
              << std::setw(6) << std::setfill('0') << new_hhmmss << std::endl;
}

int main() {
    int yyyymmdd = 20231118; // 입력된 8자리 날짜 (예: 2023-11-18)
    int hhmmss = 235959;     // 입력된 6자리 시간 (예: 23:59:59)

    std::cout << "Original datetime: " << yyyymmdd << " " << hhmmss << std::endl;

    // -1초 계산
    calculate_datetime(yyyymmdd, hhmmss, -1);

    // +1초 계산
    calculate_datetime(yyyymmdd, hhmmss, 1);

    return 0;
}
