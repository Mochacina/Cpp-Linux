#include <iostream>
#include <sys/socket.h>
#include <sys/select.h>
#include <unistd.h>

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_SET(sock, &read_fds);

    close(sock);  // ���� ����
    FD_CLR(sock, &read_fds);  // ���� ������ ���� ��ũ���� ���տ��� ����

    if (select(sock + 1, &read_fds, NULL, NULL, NULL) < 0) {
        perror("select");
        return 1;  // select�� ���������� �۵�
    }

    return 0;
}