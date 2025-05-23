#include <iostream>
#include <sys/socket.h>
#include <sys/select.h>
#include <unistd.h>

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_SET(sock, &read_fds);

    close(sock);  // 소켓 닫음
    FD_CLR(sock, &read_fds);  // 닫힌 소켓을 파일 디스크립터 집합에서 제거

    if (select(sock + 1, &read_fds, NULL, NULL, NULL) < 0) {
        perror("select");
        return 1;  // select가 정상적으로 작동
    }

    return 0;
}