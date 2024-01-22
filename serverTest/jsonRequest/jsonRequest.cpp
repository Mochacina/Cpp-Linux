#include <iostream>
#include <sstream>
#include <curl/curl.h>
#include <cstring>
//#include "json.hpp"

using namespace std;

// �ݹ� �Լ� - CURL_WRITEFUNCTION �� ���
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
            cerr << "libcurl �ʱ�ȭ ����" << endl;
            return 0;
    }

    string url = "http://172.16.140.136:10005/eai/internaltest";
    string jsonData = returnString(num);

    // URL ����
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    // POST ��û ����
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    //curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "Test_String_From_172.16.120.89");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());

    // ���� �����͸� ������ ����
    std::string response_data;

    // �ݹ� �Լ��� �̿��Ͽ� ���� ������ ����
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_data);

    // HTTP ����� Content-Type ����
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    CURLcode res;
    res = curl_easy_perform(curl);

    // ��û ���� ���� Ȯ��
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    } else {
        // ���� ���
        std::cout << "���� ������:\n" << response_data << std::endl;
    }

    // HTTP ��� ����
    curl_slist_free_all(headers);

    // CURL �ڵ� ����
    curl_easy_cleanup(curl);

    // libcurl ����
    //curl_global_cleanup();

    return 0; 
}

int main(){
    // ��û ����
    for(int i = 1; i<=5; i++){
        cout << i << " ��° ����Ǵ� ���Դϴ�." << endl;
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