#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
    string filePath = "./test2.ini";
    int testVal = 0;

    ifstream inputFile(filePath);
    if (inputFile.is_open()){
        cout << "File open." << endl;
        inputFile >> testVal;
        inputFile.close();
    } else {
        cout << "경로에 파일이 존재하지 않아 새로운 파일을 생성합니다." << endl;
        testVal = 0;
        ofstream outputFile(filePath);
        if (outputFile.is_open()){
            outputFile << testVal;
            outputFile.close();
        } else {
            cerr << "파일 생성 에러." << endl;
            return 1;
        }
    }

    cout << "testVal: " << testVal << endl;
    testVal += 1;

    // 파일에 값 쓰기
    ofstream outputFile(filePath);
    if (outputFile.is_open()) {
        outputFile << testVal;
        outputFile.close();
    } else {
        std::cerr << "파일을 열 수 없습니다: " << filePath << std::endl;
        return 1;
    }

    std::cout << "증가된 값: " << testVal << std::endl;

    return 0;
}