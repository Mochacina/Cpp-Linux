#include <iostream>
#include <curl/curl.h>

// 콜백 함수 - CURL_WRITEFUNCTION 에 사용
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t total_size = size * nmemb;
    output->append((char*)contents, total_size);
    return total_size;
}

int main() {
    CURL* curl;
    CURLcode res;

    // libcurl 초기화
    //curl_global_init(CURL_GLOBAL_DEFAULT);

    // CURL 핸들 생성
    curl = curl_easy_init();
    if (!curl) {
        std::cerr << "libcurl 초기화 실패" << std::endl;
        return 1;
    }
    // RESTful API URL 설정
    const char* url = "https://jsonplaceholder.typicode.com/posts";

    // POST 데이터 설정 (JSON 형식)
    const char* post_data = R"({"title":"foo","body":"bar","userId":1})";

    // URL 설정
    curl_easy_setopt(curl, CURLOPT_URL, url);

    // POST 요청 설정
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);

    // 응답 데이터를 저장할 변수
    std::string response_data;

    // 콜백 함수를 이용하여 응답 데이터 수신
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

    // HTTP 헤더에 Content-Type 설정
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    // 요청 수행
    res = curl_easy_perform(curl);

    // 요청 성공 여부 확인
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    } else {
        // 응답 출력
        std::cout << "응답 데이터:\n" << response_data << std::endl;
    }

    // HTTP 헤더 정리
    curl_slist_free_all(headers);

    // CURL 핸들 정리
    curl_easy_cleanup(curl);

    // libcurl 정리
    //curl_global_cleanup();

    return 0;
}