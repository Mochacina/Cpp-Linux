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

string returnString(int i, int n);

struct requestObject {
    string url;
    int threadNum;
    int count;
};

// curl POST ��û�� �����ϴ� �Լ�
void* sendPostRequest(void* arg) {
    requestObject* obj = static_cast<requestObject*>(arg);
    
    int count = obj->count;
    int n = obj->threadNum;

    for (int i=1;i<=count;i++){
        CURL* curl;
        CURLcode res;

        //string url = "http://172.16.140.136:10005/eai/internaltest";
        string url = ((obj->url).empty()) ? "http://172.16.140.136:10005/eai/internaltest" : obj->url;
        string postData = returnString(i,n);

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
                cout << "Thread Number: " << n << " / Count: " << i << endl;
                std::cout << "Response: " << response << std::endl;
            }

            // HTTP ��� ����
            curl_slist_free_all(headers);

            // curl ����
            curl_easy_cleanup(curl);
        }
    }

    delete obj;

    pthread_exit(nullptr);
}

int main() {
    //const int numThreads = 30; // ������ ������ ����  

    // libcurl �ʱ�ȭ
    curl_global_init(CURL_GLOBAL_DEFAULT);

    string input;
    int numThreads;
    int count;

    cout << "Enter a Test URL. (If (input).empty(), use the default URL)\n: ";
    getline(cin, input);
    cout << "Enter the total number of threads.\n: ";
    cin >> numThreads;
    cout << "Enter the test iterations.\n: ";
    cin >> count;

    pthread_t threads[numThreads];

    // ���� ���� ������ ����
    for (int i = 1; i <= numThreads; ++i) {
        requestObject* obj = new requestObject;
        obj->url = input;
        obj->threadNum = i;
        obj->count = count;

        cout << "Request number:" << i << endl;
        if (pthread_create(&threads[i-1], nullptr, sendPostRequest, (void*)obj) != 0) {
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
string returnString(int i, int n){
    // "Test_Number": ")" + to_string(n) + R"(",
    string data = 
        R"({
            "Test_Count": ")" + to_string(i) + R"(",
            "Thread_Number": ")" + to_string(n) + 
             + R"("})";

    return data;
}