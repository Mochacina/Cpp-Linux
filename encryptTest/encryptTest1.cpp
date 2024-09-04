#include "./3DES_hex.hpp"
#include <bits/stdc++.h>

using namespace std;

int main(){
    char szresult[2048];
    memset(szresult, 0x00, sizeof(szresult));

    char szPlain[30+1];
    memset(szPlain, 0x00, sizeof(szPlain));

    strncpy(szPlain, "TestString", sizeof("TestString"));

    cout << "Plain Text: " << szPlain << endl;

    ENDECRYPT(szPlain,
            "30",
            "F",		// ¾ÏÈ£È­ 
            szresult);
    
    cout << "Result: " << szresult << endl;

    return 0;
}
