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
        "Test_Number": ")" + to_string(n) + R"(",
        "OTRS_DLNG_NO": "8078",
        "DPWD_OTRS_TGRM_CNTN": [],
        "OPSTR_INFO_TGRM_CNTN": [],
        "CTML_EQM_NO": "06380002930",
        "CALM_DPWD_AMH_TGRM_CNTN": [],
        "CTML_JB_DVS_CD": "1250",
        "AMH_MYDP_COLC_TGRM_CNTN": [],
        "DEVICE_NAME": "CHTER",
        "OTRS_CTML_EQM_NO": "06380007281",
        "AREA_CODE": "0101",
        "HNET_TGRM_TPE_CD": "0310",
        "DEPT_NO": "14",
        "GFCET_SNO_TGRM_CNTN": [
            {
                "TranType": "1",
                "AdminID": "001299    ",
                "ItemCode": "49",
                "UserName": "                    ",
                "TotalRecordCnt": "00001",
                "GiftList": [
                    {
                        "GiftType": "K",
                        "GiftTypeCode": "2  ",
                        "GiftSeqNo": "6135000000720     ",
                        "GiftIssuerCode": "F"
                    }
                ],
                "AdminAgencyUserID": "          ",
                "ItemLength": "0102",
                "PosNo": "9610",
                "TranKind": "200",
                "AdminAgencyUserName": "                    "
            }
        ],
        "AMH_COLC_GFCET_TGRM_CNTN": [],
        "GFCET_DPS_INFO_TGRM_CNTN": [
            {
                "TranType": "1",
                "GiftInCnt5000_F": "00000",
                "GiftInCnt5000_G": "00000",
                "BagGiftInCnt10000_I": "00000",
                "BagGiftInCnt10000_H": "00000",
                "BagGiftInCnt10000_G": "00000",
                "GiftInCnt50000_6": "00000",
                "BagGiftInCnt10000_F": "00000",
                "GiftInCnt5000_H": "00000",
                "GiftInCnt5000_I": "00000",
                "GiftInCnt5000_6": "00000",
                "BagGiftTotalAmt_I": "00000000000",
                "BagGiftTotalAmt_G": "00000000000",
                "BagGiftTotalAmt_H": "00000000000",
                "BagGiftTotalAmt_F": "00000000000",
                "GiftInCnt50000_I": "00000",
                "GiftInCnt50000_H": "00000",
                "GiftInCnt50000_G": "00000",
                "GiftInCnt50000_F": "00000",
                "BagTotalCnt_F": "00001",
                "BagTotalCnt_G": "00000",
                "BagTotalCnt_H": "00000",
                "BagGiftInCnt30000_I": "00000",
                "BagGiftInCnt30000_H": "00000",
                "BagTotalCnt_I": "00000",
                "BagGiftInCnt1000_6": "00000",
                "GiftInCnt1000_6": "00000",
                "GiftInCnt70000_F": "00000",
                "GiftInCnt70000_G": "00000",
                "BagGiftInCnt2000_I": "00000",
                "GiftInCnt300000_6": "00000",
                "GiftInCnt70000_H": "00000",
                "BagGiftInCnt2000_H": "00000",
                "BagGiftInCnt2000_G": "00000",
                "GiftInCnt70000_I": "00000",
                "BagGiftInCnt2000_F": "00000",
                "BagTotalCnt_6": "00000",
                "BagGiftInCnt1000_F": "00000",
                "BagGiftInCnt1000_G": "00000",
                "GiftInCnt1000_F": "00000",
                "GiftInCnt1000_G": "00000",
                "GiftInCnt300000_F": "00001",
                "BagGiftInCnt30000_G": "00000",
                "GiftInCnt10000_H": "00000",
                "GiftInCnt1000_H": "00000",
                "BagGiftInCnt30000_F": "00000",
                "GiftInCnt300000_G": "00000",
                "GiftInCnt10000_I": "00000",
                "GiftInCnt1000_I": "00000",
                "BagGiftInCnt2000_6": "00000",
                "GiftInCnt10000_F": "00000",
                "GiftInCnt300000_H": "00000",
                "BagGiftInCnt1000_H": "00000",
                "TranKind": "200",
                "GiftInCnt10000_G": "00000",
                "GiftInCnt300000_I": "00000",
                "BagGiftInCnt1000_I": "00000",
                "BagGiftInCnt5000_6": "00000",
                "GiftInCnt10000_6": "00000",
                "GiftInCnt70000_6": "00000",
                "BagGiftInCnt100000_H": "00000",
                "BagGiftInCnt100000_I": "00000",
                "BagGiftInCnt300000_H": "00000",
                "BagGiftInCnt5000_I": "00000",
                "BagGiftInCnt5000_H": "00000",
                "BagGiftInCnt300000_I": "00000",
                "PosNo": "9610",
                "BagGiftInCnt300000_F": "00000",
                "BagGiftInCnt100000_F": "00000",
                "BagGiftInCnt300000_G": "00000",
                "BagGiftInCnt100000_G": "00000",
                "BagGiftInCnt5000_G": "00000",
                "BagGiftInCnt5000_F": "00000",
                "AdminAgencyUserID": "          ",
                "BagGiftInCnt300000_6": "00000",
                "BagGiftInCnt100000_6": "00000",
                "BagGiftInCnt50000_6": "00000",
                "GiftIssue_6": "6",
                "BagGiftInCnt30000_6": "00000",
                "BagGiftInCnt500000_G": "00000",
                "BagGiftInCnt500000_F": "00000",
                "BagGiftInCnt50000_F": "00000",
                "BagGiftInCnt500000_I": "00000",
                "BagGiftInCnt50000_G": "00000",
                "BagGiftInCnt500000_H": "00000",
                "BagGiftInCnt50000_H": "00000",
                "BagGiftInCnt50000_I": "00000",
                "GiftIssue_G": "G",
                "GiftIssue_F": "F",
                "GiftIssue_I": "I",
                "GiftIssue_H": "H",
                "ItemLength": "0714",
                "GiftInCnt500000_6": "00000",
                "AdminID": "001299    ",
                "ItemCode": "48",
                "GiftInCnt100000_6": "00000",
                "GiftInCnt2000_I": "00000",
                "GiftInCnt2000_F": "00000",
                "GiftTotalAmt_6": "00000000000",
                "GiftInCnt2000_H": "00000",
                "GiftInCnt2000_G": "00000",
                "GiftInCnt500000_F": "00000",
                "GiftInCnt30000_6": "00000",
                "GiftInCnt500000_G": "00000",
                "GiftInCnt100000_F": "00000",
                "GiftTotalAmt_I": "00000000000",
                "GiftInCnt100000_G": "00000",
                "GiftTotalAmt_G": "00000000000",
                "GiftTotalAmt_H": "00000000000",
                "GiftInCnt2000_6": "00000",
                "GiftTotalAmt_F": "00000300000",
                "GiftInCnt500000_H": "00000",
                "GiftInCnt100000_H": "00000",
                "BagGiftInCnt500000_6": "00000",
                "GiftInCnt500000_I": "00000",
                "GiftInCnt100000_I": "00000",
                "GiftInCnt30000_G": "00000",
                "GiftInCnt30000_F": "00000",
                "UserName": "                    ",
                "BagGiftTotalAmt_6": "00000000000",
                "BagGiftInCnt70000_6": "00000",
                "GiftInCnt30000_I": "00000",
                "AdminAgencyUserName": "                    ",
                "GiftInCnt30000_H": "00000",
                "BagGiftInCnt70000_H": "00000",
                "BagGiftInCnt70000_I": "00000",
                "BagGiftInCnt10000_6": "00000",
                "BagGiftInCnt70000_F": "00000",
                "BagGiftInCnt70000_G": "00000"
            }
        ],
        "CALM_DPS_DLNG_TGRM_CNTN": [
            {
                "TranType": "1",
                "BagEuroInCnt5": "00000",
                "BillOutCnt50000": "00000",
                "BagDollarInCnt10": "00000",
                "BillOutCnt100000": "00000",
                "BagCheckInCnt300000": "00000",
                "GiftOutCnt5000": "00000",
                "YuanCnt100": "00000",
                "DollarInCnt10": "00000",
                "BagCheckInCnt1000000": "00000",
                "EuroInCnt100": "00000",
                "BagYuanCnt20": "00000",
                "EuroInCnt500": "00000",
                "BagBillOutCnt5000": "00000",
                "BillInCnt100000": "00000",
                "BillInCnt1000": "00000",
                "GiftOutCnt100000": "00000",
                "BagEuroInCnt50": "00000",
                "BagInCorpGiftAmt": "00000000000",
                "BillInCnt50000": "00000",
                "BagYenInCnt1000": "00000",
                "OutCorpGiftAmt": "00000000000",
                "EuroInCnt50": "00000",
                "DollarInCnt100": "00000",
                "BagAllianceGiftAmt": "00000000000",
                "CheckInCnt100000": "00000",
                "BagEuroInCnt20": "00000",
                "BagYuanCnt1": "00000",
                "BagYuanCnt2": "00000",
                "BagEuroInCnt500": "00000",
                "BagYuanCnt5": "00000",
                "YenInCnt10000": "00000",
                "BagEuroInCnt100": "00000",
                "BagYuanCnt100": "00000",
                "BagOutCorpGiftCnt": "00000",
                "CoinOutCnt50": "00000",
                "BagCoinOutCnt10": "00000",
                "TranKind": "200",
                "DollarInCnt5": "00000",
                "YenInCnt2000": "00000",
                "BillOutCnt1000": "00000",
                "BagDollarInCnt20": "00000",
                "DollarInCnt1": "00000",
                "DollarInCnt2": "00000",
                "CoinInCnt50": "00000",
                "BagYenInCnt10000": "00000",
                "DollarInCnt20": "00000",
                "YenInCnt5000": "00000",
                "YenInCnt1000": "00000",
                "BagDollarInCnt50": "00000",
                "CoinOutCnt100": "00000",
                "CoinOutCnt500": "00000",
                "BagDollarInCnt5": "00000",
                "BagDollarInCnt2": "00000",
                "PosNo": "9610",
                "BagDollarInCnt1": "00000",
                "GiftOutCnt50000": "00000",
                "BagBillOutCnt1000": "00000",
                "BagEuroInCnt200": "00000",
                "CheckInCnt300000": "00000",
                "AdminAgencyUserID": "          ",
                "BagYenInCnt2000": "00000",
                "DollarInCnt50": "00000",
                "GiftOutCnt10000": "00000",
                "BagCoinOutCnt100": "00000",
                "CoinInCnt500": "00000",
                "CheckInNonDenoAmt": "00000000000",
                "BillInCnt5000": "00000",
                "BagBillOutCnt50000": "00000",
                "BagYenInCnt5000": "00000",
                "BagEuroInCnt10": "00000",
                "BagCheckInNonDenoAmt": "00000000000",
                "BagBillOutCnt100000": "00000",
                "ItemLength": "0612",
                "CheckInCnt500000": "00000",
                "YuanCnt5": "00000",
                "AdminID": "001299    ",
                "ItemCode": "47",
                "BagCoinOutCnt50": "00000",
                "YuanCnt1": "00000",
                "EuroInCnt10": "00000",
                "YuanCnt2": "00000",
                "BagCheckInCnt500000": "00000",
                "CheckInNonDenoCnt": "00000",
                "BillOutCnt10000": "00000",
                "CoinOutCnt10": "00000",
                "CoinInCnt100": "00000",
                "InCorpGiftAmt": "00000300000",
                "YuanCnt10": "00000",
                "BagDollarInCnt100": "00000",
                "BagCheckInNonDenoCnt": "00000",
                "EuroInCnt200": "00000",
                "BagCoinOutCnt500": "00000",
                "BillOutCnt5000": "00000",
                "BagCheckInCnt100000": "00000",
                "UserName": "                    ",
                "EuroInCnt20": "00000",
                "AllianceGiftAmt": "00000000000",
                "CheckInCnt1000000": "00000",
                "AdminAgencyUserName": "                    ",
                "BagBillOutCnt10000": "00000",
                "EuroInCnt5": "00000",
                "CoinInCnt10": "00000",
                "YuanCnt20": "00000",
                "BagOutCorpGiftAmt": "00000000000",
                "BillInCnt10000": "00000",
                "BagYuanCnt10": "00000"
            }
        ],
        "HNCP_STUS_TGRM_CNTN": [],
        "POS_NO": "9610",
        "OTRS_POS_NO": "8050",
        "CTML_DVC_NO": "0638",
        "CTML_APP_VER_VAL": "20240111",
        "DLNG_YMD": "20240112",
        "OTRS_SALS_YMD": "20240112",
        "DLNG_TM": "173412",
        "OTRS_CAHR_NO": "001299",
        "DLNG_NO": "2930"
    })";

    return data;
}