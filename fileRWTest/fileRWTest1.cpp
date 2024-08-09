#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <cstdlib> // atoi 함수 사용을 위해 추가

// ini 파일을 읽어 키-값 쌍으로 저장
std::map<std::string, std::string> readIniFile(const std::string& filePath) {
    std::ifstream file(filePath.c_str()); // C++98에서는 std::ifstream을 생성할 때 C 스타일 문자열을 사용
    std::map<std::string, std::string> iniData;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        std::string key, value;

        if (std::getline(lineStream, key, '=') && std::getline(lineStream, value)) {
            iniData[key] = value;
        }
    }

    file.close();
    return iniData;
}

// 수정된 데이터를 ini 파일로 저장
void writeIniFile(const std::string& filePath, const std::map<std::string, std::string>& iniData) {
    std::ofstream file(filePath.c_str()); // C++98 스타일의 파일 경로 사용

    for (std::map<std::string, std::string>::const_iterator it = iniData.begin(); it != iniData.end(); ++it) {
        file << it->first << "=" << it->second << "\n";
    }

    file.close();
}

int main() {
    const std::string filePath = "seqnum.ini";
    const std::string key = "seqnum";

    // ini 파일 읽기
    std::map<std::string, std::string> iniData = readIniFile(filePath);

    // 특정 항목의 값을 읽어와서 증가시키기
    int value = 0;
    if (iniData.find(key) != iniData.end()) {
        value = std::atoi(iniData[key].c_str()); // std::stoi 대신 std::atoi 사용
    }

    std::cout << "현재 값: " << value << std::endl;

    // 값 증가시키기
    value += 1;

    std::ostringstream oss;
    oss << value;
    iniData[key] = oss.str(); // std::to_string 대신 stringstream을 사용하여 문자열로 변환

    // 증가된 값을 파일에 다시 저장
    writeIniFile(filePath, iniData);

    std::cout << "증가된 값: " << value << std::endl;

    return 0;
}
