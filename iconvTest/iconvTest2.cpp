#include "./libiconv/inc/iconv.h"
#include <bits/stdc++.h>

using namespace std;

string convert_encoding(const std::string& input, const char* from_enc, const char* to_enc);

int main (int argc, char* argv[]) {
    std::string input = "Hello, World!\n��� ����";

    std::string converted = convert_encoding(input, "UTF-8", "EUC-KR");

    // ��ȯ�� ���ڿ��� ���Ͽ� ���
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

// ��ƿ��Ƽ �Լ�: iconv�� ����Ͽ� ���ڵ� ��ȯ
std::string convert_encoding(const std::string& input, const char* from_enc, const char* to_enc) {
    iconv_t cd = iconv_open(to_enc, from_enc);
    if (cd == (iconv_t)-1) {
        perror("iconv_open failed");
        return "";
    }

    size_t in_size = input.size();
    size_t out_size = in_size * 4;  // ����Ǵ� �ִ� ��� ũ�� (UTF-8�� �� ����� �� ����)
    char* in_buf = const_cast<char*>(input.data());
    std::string output(out_size, 0); // ����� ũ���� ��� ���� ����
    char* out_buf = &output[0];

    // iconv ��ȯ ����
    size_t result = iconv(cd, &in_buf, &in_size, &out_buf, &out_size);
    if (result == (size_t)-1) {
        perror("iconv conversion failed");
        iconv_close(cd);
        return "";
    }

    iconv_close(cd);
    output.resize(output.size() - out_size); // ��ȯ�� ũ�⿡ �°� ���ڿ� ũ�� ����
    return output;
}