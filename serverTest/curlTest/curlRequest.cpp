#include <iostream>
#include <curl/curl.h>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t total_size = size * nmemb;
    output->append((char*)contents, total_size);
    return total_size;
}

int main () {
    // libcurl 초기화
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "libcurl 초기화 실패" << std::endl;
        return 1;
    }

    const char* url = "http://httpbin.org/get";

    curl_easy_setopt(curl, CURLOPT_URL, url);

    std::string response_data;

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

    CURLcode res = curl_easy_perform(curl);

    // 요청 결과 확인
    if (res != CURLE_OK) {
        std::cerr << "libcurl 요청 실패: " << curl_easy_strerror(res) << std::endl;
    } else {
        std::cout << "서버 응답:\n" << response_data << std::endl;
    }

    // libcurl 해제
    curl_easy_cleanup(curl);

    return 0;
}