#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "cJSON-master/cJSON.h"

using namespace std;

int main () {
    string _str = R"({
        "number": 1,
        "testString": "test",
        "testArray": [
            {
                "numberInArray": 2,
                "stringInArray": "testInArray"
            }
        ]
    })";

    cJSON* jsonData = cJSON_Parse(_str.c_str());

    if(jsonData == nullptr){
        cout << "Error: Parse Fail jsonData." << endl;
        return -1;
    }

    cJSON* number = cJSON_GetObjectItemCaseSensitive(jsonData, "number");
    cJSON* testString = cJSON_GetObjectItemCaseSensitive(jsonData, "testString");
    cJSON* testArray = cJSON_GetObjectItemCaseSensitive(jsonData, "testArray");
    
    cout << "==== TEST ====" << endl;
    cout << cJSON_GetObjectItemCaseSensitive(jsonData, "testString")->valuestring << endl;
    cout << "==== TEST ====" << endl;

    if(cJSON_IsNumber(number)){
        cout << "number: " << number->valueint << endl;
    } else {
        cout << "number is not number type." << endl;
    }

    if(cJSON_IsString(testString)){
        cout << "testString: " << testString->valuestring << endl;
    } else {
        cout << "testString is not string type." << endl;
    }

    if(cJSON_IsArray(testArray)){
        cout << "testArray:" << endl;
        for (int i = 0; i < cJSON_GetArraySize(testArray); ++i) {
            cJSON* item = cJSON_GetArrayItem(testArray, i);
            cJSON* itemNumberInArray = cJSON_GetObjectItemCaseSensitive(item, "numberInArray");
            cJSON* itemStringInArray = cJSON_GetObjectItemCaseSensitive(item, "stringInArray");

            if (cJSON_IsNumber(itemNumberInArray)) {
                cout << " ↘ numberInArray: " << itemNumberInArray->valuedouble << endl;
            }

            if (cJSON_IsString(itemStringInArray)) {
                cout << " ↘ stringInArray: " << itemStringInArray->valuestring << endl;
            }
        }
    } else {
        cout << "testArray is not array." << endl;
    }

    // 기타 필요한 코드 및 리소스 정리

    cJSON_Delete(jsonData); // 할당된 메모리를 해제하는 코드 추가

    return 0;
}