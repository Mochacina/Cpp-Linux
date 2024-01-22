#include <iostream>
#include <cstring>
#include <pthread.h>
#include <curl/curl.h>
#include <mutex>

using namespace std;

// curl �ݹ� �Լ�
size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

string returnString(int num);

// curl POST ��û�� �����ϴ� �Լ�
void* sendPostRequest(void* arg) {
    int* num = static_cast<int*>(arg);
    int n = *num;

    CURL* curl;
    CURLcode res;
    string url = "http://172.16.140.136:10005/eai/internaltest";
    string postData = returnString(n);
    
    curl = curl_easy_init();
    if (curl) {
        // URL ����
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // POST ������ ����
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());

        // ���� �����͸� ���� ���ڿ� ����
        string response;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // HTTP ����� Content-Type ����
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // POST ��û ������
        res = curl_easy_perform(curl);

        // ��� Ȯ�� (Response Number üũ�ϱ�)
        if (res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        } else {
            cout << "Response Number: " << n << endl;
            //std::cout << "Response: " << response << std::endl;
        }

        // HTTP ��� ����
        curl_slist_free_all(headers);

        // curl ����
        curl_easy_cleanup(curl);
    }

    pthread_exit(nullptr);
}

int main() {
    const int numThreads = 800; // ������ ������ ����
    pthread_t threads[numThreads];

    // libcurl �ʱ�ȭ
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // ���� ���� ������ ����
    for (int i = 1; i <= numThreads; ++i) {
        cout << "Request number:" << i << endl;
        if (pthread_create(&threads[i-1], nullptr, sendPostRequest, (void*)&i) != 0) {
            cerr << "Failed to create thread " << i << endl;
            return 1;
        }
    }

    // �� ������ ���� ���
    for (int i = 0; i < numThreads; ++i) {
        pthread_join(threads[i], nullptr);
    }

    // libcurl ����
    curl_global_cleanup();

    return 0;
}

// �ż��� ������ ���� ���ڿ� �����ϴ� �Լ�
string returnString(int n){
    // "Test_Number": ")" + to_string(n) + R"(",
    string data = R"({
        "testData": "1234"
    })";

    return data;
}