#include "./3DES_hex.hpp"
#include <bits/stdc++.h>

using namespace std;

int main(){
    char szresult[2048];
    memset(szresult, 0x00, sizeof(szresult));

    char szresult2[2048];
    memset(szresult2, 0x00, sizeof(szresult2));

    char szPlain[30+1];
    memset(szPlain, 0x20, sizeof(szPlain)-1);

    cout << "암호화 할 평문을 입력하세요: ";

    string str;

    cin >> str;

    strncpy(szPlain, str.c_str(), str.size());

    //strncpy(szPlain, "123456", sizeof("TestString"));

    cout << "Plain Text: '" << szPlain << "'" << endl;

    ENDECRYPT(szPlain,
            "30",
            "F",
            szresult);
    
    ENDECRYPT(szresult,
            "60",
            "B",
            szresult2);
    
    cout << "Encrypt Result: " << szresult << endl;
    cout << "Decrypt Result: " << szresult2 << endl;

    return 0;
}
