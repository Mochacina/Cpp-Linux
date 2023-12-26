#include <curl/curl.h>
#include <iostream>
#include <httplib.h>  // cpp-httplib 라이브러리 사용

// HTTP GET 요청을 보내는 함수
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t total_size = size * nmemb;
    output->append((char*)contents, total_size);
    return total_size;
}

// REST API 서버 핸들러
void HelloHandler(const httplib::Request& req, httplib::Response& res) {
    // cURL 초기화
    CURL* curl;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (!curl) {
        std::cerr << "cURL 초기화 실패" << std::endl;
        res.status = 500;  // 서버 오류
        return;
    }

    // 다른 API 서버로의 요청을 보낼 URL 설정
    std::string otherApiUrl = https://api.example.com/data;

    // cURL 옵션 설정
    curl_easy_setopt(curl, CURLOPT_URL, otherApiUrl.c_str());

    // 응답을 저장할 문자열
    std::string response;

    // 데이터 수신 콜백 함수 설정
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // HTTP GET 요청 보내기
    CURLcode resCurl = curl_easy_perform(curl);

    // 결과 확인 및 출력
    if (resCurl != CURLE_OK) {
        std::cerr << "다른 API 서버로의 cURL 요청 실패: " << curl_easy_strerror(resCurl) << std::endl;
        res.status = 500;  // 서버 오류
    } else {
        std::cout << "다른 API 서버 응답: " << response << std::endl;

        // 클라이언트에 응답 전송
        res.set_content(response, "application/json");
    }

    // cURL 정리
    curl_easy_cleanup(curl);
    curl_global_cleanup();
}

int main() {
    // cpp-httplib 서버 초기화
    httplib::Server svr;

    // 루트 핸들러 설정
    svr.Get("/", HelloHandler);

    // 서버 시작
    svr.listen("localhost", 8080);

    return 0;
}
