#include "./libiconv/inc/iconv.h"
#include <bits/stdc++.h>

using namespace std;

string convert_encoding(const std::string& input, const char* from_enc, const char* to_enc);

int main (int argc, char* argv[]) {
    std::string input = "Hello, World!\n헬로 월드";

    std::string converted = convert_encoding(input, "UTF-8", "EUC-KR");

    // 변환된 문자열을 파일에 기록
    std::ofstream outfile("output.txt");
    if (outfile.is_open()) {
        outfile << converted;
        outfile.close();
        std::cout << "File written with EUC-KR encoding." << std::endl;
    } else {
        std::cerr << "Unable to open file for writing." << std::endl;
    }
    
    return 0;
}

// 유틸리티 함수: iconv를 사용하여 인코딩 변환
std::string convert_encoding(const std::string& input, const char* from_enc, const char* to_enc) {
    iconv_t cd = iconv_open(to_enc, from_enc);
    if (cd == (iconv_t)-1) {
        perror("iconv_open failed");
        return "";
    }

    size_t in_size = input.size();
    size_t out_size = in_size * 4;  // 예상되는 최대 출력 크기 (UTF-8이 더 길어질 수 있음)
    char* in_buf = const_cast<char*>(input.data());
    std::string output(out_size, 0); // 충분한 크기의 출력 버퍼 생성
    char* out_buf = &output[0];

    // iconv 변환 수행
    size_t result = iconv(cd, &in_buf, &in_size, &out_buf, &out_size);
    if (result == (size_t)-1) {
        perror("iconv conversion failed");
        iconv_close(cd);
        return "";
    }

    iconv_close(cd);
    output.resize(output.size() - out_size); // 변환된 크기에 맞게 문자열 크기 조정
    return output;
}