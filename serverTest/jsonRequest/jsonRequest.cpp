#include <iostream>
#include <curl/curl.h>
#include "json.hpp"

using namespace std;

// 콜백 함수 - CURL_WRITEFUNCTION 에 사용
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t total_size = size * nmemb;
    output->append((char*)contents, total_size);
    return total_size;
}

string returnString();

int main(){

    string url = "http://httpbin.org/post";
    string jsonData = returnString();

    CURL* curl;

    curl = curl_easy_init();
    if (!curl) {
        cerr << "libcurl 초기화 실패" << endl;
        return 0;
    }

    // URL 설정
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    // POST 요청 설정
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
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

    // 요청 수행
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

string returnString(){
    string data = R"({
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