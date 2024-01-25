#include <iostream>
#include <cstring>
#include <pthread.h>
#include <curl/curl.h>
#include <mutex>

using namespace std;
int req_T = 0;
int req_F = 0;

string defaultURL = "http://172.16.140.136:10005/eai/internaltest";

// curl �ݹ� �Լ�
size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

string returnString(int i, int n);

// request�� ����� ������ ����ü
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

        
        string url = ((obj->url).empty()) ? defaultURL : obj->url;
        string postData = returnString(i,n);

        curl = curl_easy_init();
        if (curl) {
            // Timeout ����
            curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10); // 30�ʷ� ����

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
            //cout << "thNum: " << n << " / Request number:" << i << endl;
            res = curl_easy_perform(curl);

            // ��� Ȯ�� (Response Number üũ�ϱ�)
            if (res != CURLE_OK) {
                cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
                req_F += 1;
            } else {
                cout << "Thread Number: " << n << " / Count: " << i << endl;
                req_T += 1;
                //std::cout << "Response: " << response << std::endl;
            }

            // HTTP ��� ����
            curl_slist_free_all(headers);

            // curl ����
            curl_easy_cleanup(curl);
        }
    }

    // �޸� ����
    delete obj;

    pthread_exit(nullptr);
}

int main() {
    // libcurl �ʱ�ȭ
    curl_global_init(CURL_GLOBAL_DEFAULT);

    string input;
    int numThreads = 0;
    int count = 0;

    cout << "Enter a Test URL. (If input is empty(), use the default URL)\n";
    cout << "default URL = " << defaultURL << "\n: ";
    getline(cin, input);
    while(1){
        cout << "Enter the total number of threads. (Max 1000)\n: ";
        cin >> numThreads;
        if(cin.fail() || (numThreads < 1 || numThreads > 1000)){
            cout << "Invaild value. Try again." << endl;
            cin.clear(); // ���� �÷��׸� �ʱ�ȭ�Ͽ� �Է� ��Ʈ���� ���� ���·� ��ȯ
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // �߸��� �Է� ����
        } else break;
    }
    while(1){
        cout << "Enter the test iterations. (Max 1000)\n: ";
        cin >> count;
        if(cin.fail() || (count < 1 || count > 1000)){
            cout << "Invaild value. Try again." << endl;
            cin.clear(); // ���� �÷��׸� �ʱ�ȭ�Ͽ� �Է� ��Ʈ���� ���� ���·� ��ȯ
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // �߸��� �Է� ����
        } else break;
    }

    pthread_t threads[numThreads];

    // ���� ���� ������ ����
    for (int i = 1; i <= numThreads; ++i) {
        // requestObject �����͸� ������ ����ü�� ���� �޸𸮿� ����
        requestObject* obj = new requestObject;
        obj->url = input;
        obj->threadNum = i;
        obj->count = count;

        cout << "Create Thread: " << i << endl;

        if (pthread_create(&threads[i-1], nullptr, sendPostRequest, (void*)obj) != 0) {
            cerr << "Failed to create thread " << i << endl;
            return 1;
        }
    }

    // �� ������ ���� ���
    for (int i = 0; i < numThreads; ++i) {
        pthread_join(threads[i], nullptr);
    }

    cout << "Total Success: " << req_T << endl;
    cout << "Total Fail: " << req_F << endl;

    // libcurl ����
    curl_global_cleanup();

    return 0;
}

// ������ ���� ���ڿ� �����ϴ� �Լ�
string returnString(int i, int n){
    // "Test_Number": ")" + to_string(n) + R"(",
    string data = 
        R"({
            "Test_Count": ")" + to_string(i) + R"(",
            "Thread_Number": ")" + to_string(n) + 
             + R"("})";

    return data;
}