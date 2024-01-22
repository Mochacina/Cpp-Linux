#include <iostream>
#include <sstream>
#include <curl/curl.h>
#include <cstring>
//#include "json.hpp"

using namespace std;

// 콜백 함수 - CURL_WRITEFUNCTION 에 사용
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t total_size = size * nmemb;
    output->append((char*)contents, total_size);
    return total_size;
}

string returnString(int* num);

void* curl_async(void* data){
    int* num = static_cast<int*>(data);

    CURL* curl; 
    curl = curl_easy_init();
    if (!curl) {
            cerr << "libcurl 초기화 실패" << endl;
            return 0;
    }

    string url = "http://172.16.140.136:10005/eai/internaltest";
    string jsonData = returnString(num);

    // URL 설정
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    // POST 요청 설정
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    //curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "Test_String_From_172.16.120.89");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());

    // 응답 데이터를 저장할 변수
    std::string response_data;

    // 콜백 함수를 이용하여 응답 데이터 수신
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

    // HTTP 헤더에 Content-Type 설정
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    CURLcode res;
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

int main(){
    // 요청 수행
    for(int i = 1; i<=5; i++){
        cout << i << " 번째 수행되는 중입니다." << endl;
        pthread_t thread_client;
        pthread_create(&thread_client, NULL, curl_async, (void*)&i);
    }
    return 0;
}

string returnString(int* num){
    int n;
    memcpy(&n, num, sizeof(num));
    string data = R"({
        "testData": "1234"
    })";

    return data;
}