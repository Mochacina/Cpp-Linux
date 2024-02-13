#include <iostream>
#include <cstring>
#include <stdlib.h>

using namespace std;

int main() {
    char result[160+1];

    memset(result, 0x00, sizeof(result));
    cout << result << endl;
    
    for (int i = 0; i < 10; i++) {
        char c = static_cast<char>(i + 48); // ASCII 코드에서 숫자로 변환
        cout << c << endl;

        char buffer[16];
        memset(buffer, 0x00, sizeof(buffer));
        memcpy(buffer, &c, sizeof(c));
        cout << buffer << endl;

        strcat(buffer, " Hello, World! ");
        cout << buffer << endl;

        if (i == 0){
            strcpy(result, buffer);
        } else {
            strcat(result, buffer);
        }
        
    }

    cout << result << endl;
    cout << strlen(result) << endl;
}