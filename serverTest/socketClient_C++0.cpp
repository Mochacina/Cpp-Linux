#include <iostream>
#include <cstring>
#include <pthread.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <exception>
using namespace std;

#define PACKET_SIZE 1024
// #define serverPort 7000
int server_socket;

void* proc_recv(void* data) {
    char buffer[PACKET_SIZE] = {};
    while (1) {
        memset(buffer, 0, PACKET_SIZE);
        ssize_t recvSize = recv(server_socket, buffer, PACKET_SIZE, 0);
        if (recvSize > 0) {
            cout << "���� �޼���: " << buffer << endl;
        } else if (recvSize == 0) {
            cout << "���� ������ ����Ǿ����ϴ�." << endl;
            terminate();
            break;
        } else {
            cerr << "���� ����" << endl;
            break;
        }
    }
    return NULL;
}

int main() {

    int serverPort;
    string serverIpAddr;

    cout << "���� IP Address�� �Է��ϼ���: ";
    cin >> serverIpAddr;
    cout << "���� Port Number�� �Է��ϼ���: ";
    cin >> serverPort;

    const char* ipAddressCString = serverIpAddr.c_str();

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        cerr << "���� ���� ����" << endl;
        return 1;
    }

    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(serverPort);
    addr.sin_addr.s_addr = inet_addr(ipAddressCString);

    while (1) {
        if (connect(server_socket, (struct sockaddr*)&addr, sizeof(addr)) == 0) {
            cout << "������ ����Ǿ����ϴ�." << endl;
            break;
        }
    }

    pthread_t thread_id;
    if (pthread_create(&thread_id, NULL, proc_recv, NULL) != 0) {
        cerr << "������ ���� ����" << endl;
        return 1;
    }

    char msg[PACKET_SIZE] = {0};
    while (1) {
        memset(msg, 0, PACKET_SIZE);
        cin >> msg;
        ssize_t sendSize = send(server_socket, msg, strlen(msg), 0);
        if (sendSize <= 0) {
            cerr << "���� ����" << endl;
            break;
        }
    }

    pthread_join(thread_id, NULL);
    close(server_socket);

    return 0;
}
