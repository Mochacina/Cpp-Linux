#include <curl/curl.h>
#include <iostream>
#include <httplib.h>  // cpp-httplib ���̺귯�� ���

// HTTP GET ��û�� ������ �Լ�
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t total_size = size * nmemb;
    output->append((char*)contents, total_size);
    return total_size;
}

// REST API ���� �ڵ鷯
void HelloHandler(const httplib::Request& req, httplib::Response& res) {
    // cURL �ʱ�ȭ
    CURL* curl;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (!curl) {
        std::cerr << "cURL �ʱ�ȭ ����" << std::endl;
        res.status = 500;  // ���� ����
        return;
    }

    // �ٸ� API �������� ��û�� ���� URL ����
    std::string otherApiUrl = https://api.example.com/data;

    // cURL �ɼ� ����
    curl_easy_setopt(curl, CURLOPT_URL, otherApiUrl.c_str());

    // ������ ������ ���ڿ�
    std::string response;

    // ������ ���� �ݹ� �Լ� ����
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // HTTP GET ��û ������
    CURLcode resCurl = curl_easy_perform(curl);

    // ��� Ȯ�� �� ���
    if (resCurl != CURLE_OK) {
        std::cerr << "�ٸ� API �������� cURL ��û ����: " << curl_easy_strerror(resCurl) << std::endl;
        res.status = 500;  // ���� ����
    } else {
        std::cout << "�ٸ� API ���� ����: " << response << std::endl;

        // Ŭ���̾�Ʈ�� ���� ����
        res.set_content(response, "application/json");
    }

    // cURL ����
    curl_easy_cleanup(curl);
    curl_global_cleanup();
}

int main() {
    // cpp-httplib ���� �ʱ�ȭ
    httplib::Server svr;

    // ��Ʈ �ڵ鷯 ����
    svr.Get("/", HelloHandler);

    // ���� ����
    svr.listen("localhost", 8080);

    return 0;
}
