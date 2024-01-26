#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "cJSON-master/cJSON.h"

using namespace std;

int jsonGetInt(cJSON* json, const string& name){
    cJSON* item = cJSON_GetObjectItemCaseSensitive(json, name.c_str());

    if (item == nullptr || !cJSON_IsNumber(item)) {
        throw runtime_error("Key not found or not a number");
    }
    return item->valueint;
}

string jsonGetString(cJSON* json, const string& name){
    cJSON* item = cJSON_GetObjectItemCaseSensitive(json, name.c_str());

    if (item == nullptr || !cJSON_IsString(item)) {
        throw runtime_error("Key not found or not a string");
    }
    return string(item->valuestring);
}

vector<cJSON*> jsonGetArray(cJSON* json, const string& name) {
    cJSON* item = cJSON_GetObjectItemCaseSensitive(json, name.c_str());
    if (item == nullptr || !cJSON_IsArray(item)) {
        throw runtime_error("Key not found or not an array");
    }
    vector<cJSON*> array;
    int arraySize = cJSON_GetArraySize(item);
    for (int i = 0; i < arraySize; ++i) {
        cJSON* arrayItem = cJSON_GetArrayItem(item, i);
        array.push_back(arrayItem);
    }
    return array;
}

int main () {
    string jsonstr1 = R"({
        "number": 1,
        "testString": "test",
        "testArray": [
            {
                "numberInArray": 2,
                "stringInArray": "testInArray"
            }
        ]
    })";

    string jsonstr2 = R"({
        "name": "Awesome 4K",
        "resolutions": [
            {
                "index": 0,
                "width": 1280,
                "height": 720
            },
            {
                "index": 1,
                "width": 1920,
                "height": 1080
            },
            {
                "index": 2,
                "width": 3840,
                "height": 2160
            }
        ]
    })";

    cJSON* jsonData = cJSON_Parse(jsonstr2.c_str());

    string name = jsonGetString(jsonData, "name");
    vector<cJSON*> resolutions = jsonGetArray(jsonData, "resolutions");

    cout << "name: " << name << endl;

    for(cJSON* json : resolutions){
        int index = jsonGetInt(json, "index");
        int width = jsonGetInt(json, "width");
        int height = jsonGetInt(json, "height");

        cout << "index: " << index << endl;
        cout << "width: " << width << endl;
        cout << "height: " << height << endl;
    }

    // 기타 필요한 코드 및 리소스 정리

    cJSON_Delete(jsonData); // 할당된 메모리를 해제하는 코드 추가

    return 0;
}