#include <iostream>
#include <cstring>

using namespace std;

int main (){

    char source[1+1] = "J";
    char offerCode[1+1];

    memset(offerCode, 0x00, sizeof(offerCode));

    if(strlen(source) > 0){
        cout << "source > 0" << endl;
        if(strcmp(source, "J") == 0){
            memcpy(offerCode, "J", 1);
        } else if(strcmp(source, "K") == 0){
            memcpy(offerCode, "", 1);
        }
    }

    cout << offerCode << endl;


}