#include <iostream>
#include <string>
#include <string.h>
#include <cstring>

using namespace std;

const int MX = 1000005;
int dat[MX], pre[MX], nxt[MX];
int unused = 1;

void traverse(){
    int cur = nxt[0];
    while(cur != -1){
        cout << dat[cur] << ' ';
        cur = nxt[cur];
    }
    cout << '\n\n';
}



void insert(int addr, int num){
    dat[unused] = num;
    pre[unused] = addr;
    nxt[unused] = nxt[addr];
    nxt[addr] = unused;
    if(nxt[addr] != -1)pre[nxt[unused]] = unused;
    unused++;
}

void erase(int addr){
    dat[addr] = 0;
    nxt[pre[addr]] = nxt[addr];
    if(nxt[addr] != -1)pre[nxt[addr]] = pre[addr];
}

int main(){
    memset(dat, 0, sizeof(dat));
    fill(pre, pre+MX, -1);
    fill(nxt, nxt+MX, -1);

    return 0;
}