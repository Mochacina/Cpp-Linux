#include <iostream>
#include <iomanip>
#include <ctime>

// 8�ڸ� ��¥�� 6�ڸ� �ð��� std::tm ����ü�� ��ȯ
std::tm parse_datetime(int yyyymmdd, int hhmmss) {
    std::tm time_struct = {};
    time_struct.tm_year = (yyyymmdd / 10000) - 1900; // ���� (tm_year�� 1900 ����)
    time_struct.tm_mon = ((yyyymmdd / 100) % 100) - 1; // �� (0���� ����)
    time_struct.tm_mday = yyyymmdd % 100; // ��
    time_struct.tm_hour = hhmmss / 10000; // ��
    time_struct.tm_min = (hhmmss / 100) % 100; // ��
    time_struct.tm_sec = hhmmss % 100; // ��
    return time_struct;
}

// std::tm ����ü�� ��¥(8�ڸ�)�� �ð�(6�ڸ�)���� ��ȯ
void tm_to_datetime(const std::tm& time_struct, int &yyyymmdd, int &hhmmss) {
    yyyymmdd = (time_struct.tm_year + 1900) * 10000 + (time_struct.tm_mon + 1) * 100 + time_struct.tm_mday;
    hhmmss = time_struct.tm_hour * 10000 + time_struct.tm_min * 100 + time_struct.tm_sec;
}

// �ð��� ����ϰ� ����ϴ� �Լ�
void calculate_datetime(int yyyymmdd, int hhmmss, int adjustment) {
    // 8�ڸ� ��¥�� 6�ڸ� �ð��� std::tm ����ü�� ��ȯ
    std::tm time_struct = parse_datetime(yyyymmdd, hhmmss);

    // std::tm�� time_t�� ��ȯ
    time_t time_in_seconds = mktime(&time_struct);

    if (time_in_seconds == -1) {
        std::cerr << "Error: invalid time conversion." << std::endl;
        return;
    }

    // �� ������ ���� (+1�� �Ǵ� -1��)
    time_in_seconds += adjustment;

    // ������ �ʸ� �ٽ� std::tm���� ��ȯ
    std::tm* adjusted_time = localtime(&time_in_seconds);

    // ������ ��¥�� �ð� ���
    int new_yyyymmdd, new_hhmmss;
    tm_to_datetime(*adjusted_time, new_yyyymmdd, new_hhmmss);

    std::cout << "Adjusted datetime: "
              << new_yyyymmdd << " "
              << std::setw(6) << std::setfill('0') << new_hhmmss << std::endl;
}

int main() {
    int yyyymmdd = 20231118; // �Էµ� 8�ڸ� ��¥ (��: 2023-11-18)
    int hhmmss = 235959;     // �Էµ� 6�ڸ� �ð� (��: 23:59:59)

    std::cout << "Original datetime: " << yyyymmdd << " " << hhmmss << std::endl;

    // -1�� ���
    calculate_datetime(yyyymmdd, hhmmss, -1);

    // +1�� ���
    calculate_datetime(yyyymmdd, hhmmss, 1);

    return 0;
}
