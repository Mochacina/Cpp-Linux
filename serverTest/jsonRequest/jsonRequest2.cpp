#include <iostream>
#include <cstring>
#include <pthread.h>
#include <curl/curl.h>
#include <mutex>

using namespace std;

// curl 콜백 함수
size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

string returnString(int num);

// curl POST 요청을 수행하는 함수
void* sendPostRequest(void* arg) {
    int* num = static_cast<int*>(arg);
    int n = *num;

    CURL* curl;
    CURLcode res;
    string url = "http://172.16.140.136:10005/eai/internaltest";
    string postData = returnString(n);
    
    curl = curl_easy_init();
    if (curl) {
        // URL 설정
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // POST 데이터 설정
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());

        // 응답 데이터를 받을 문자열 설정
        string response;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // HTTP 헤더에 Content-Type 설정
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // POST 요청 보내기
        res = curl_easy_perform(curl);

        // 결과 확인 (Response Number 체크하기)
        if (res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        } else {
            cout << "Response Number: " << n << endl;
            //std::cout << "Response: " << response << std::endl;
        }

        // HTTP 헤더 정리
        curl_slist_free_all(headers);

        // curl 해제
        curl_easy_cleanup(curl);
    }

    pthread_exit(nullptr);
}

int main() {
    const int numThreads = 800; // 생성할 스레드 개수
    pthread_t threads[numThreads];

    // libcurl 초기화
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // 여러 개의 스레드 생성
    for (int i = 1; i <= numThreads; ++i) {
        cout << "Request number:" << i << endl;
        if (pthread_create(&threads[i-1], nullptr, sendPostRequest, (void*)&i) != 0) {
            cerr << "Failed to create thread " << i << endl;
            return 1;
        }
    }

    // 각 스레드 종료 대기
    for (int i = 0; i < numThreads; ++i) {
        pthread_join(threads[i], nullptr);
    }

    // libcurl 정리
    curl_global_cleanup();

    return 0;
}

// 신세계 데이터 형식 문자열 리턴하는 함수
string returnString(int n){
    // "Test_Number": ")" + to_string(n) + R"(",
    string data = R"({
        "testData": "1234"
    })";

    return data;
}