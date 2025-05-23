#include <iostream>
#include <cstring>
#include <thread>
#include <pthread.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
using namespace std;

#define PACKET_SIZE 1024
int server_socket;

void* proc_recv(void* data) {
    char buffer[PACKET_SIZE] = {};
    while (1) {
        memset(buffer, 0, PACKET_SIZE);
        ssize_t recvSize = recv(server_socket, buffer, PACKET_SIZE, 0);
        if (recvSize > 0) {
            cout << "받은 메세지: " << buffer << endl;
        } else if (recvSize == 0) {
            cout << "서버 연결이 종료되었습니다." << endl;
            exit(1);
            break;
        } else {
            cerr << "수신 오류" << endl;
            break;
        }
    }
    return nullptr;
}

int main(int argc, char* argv[]) {

    if (argc != 3) {
        cerr << "사용법: " << argv[0] << " <서버 IP 주소> <서버 포트 번호>" << endl;
        return 1;
    }

    string serverIpAddr = argv[1];
    int serverPort = atoi(argv[2]);

    const char* ipAddressCString = serverIpAddr.c_str();

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        cerr << "소켓 생성 실패" << endl;
        return 1;
    }

    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(serverPort);
    addr.sin_addr.s_addr = inet_addr(ipAddressCString);

    while (1) {
        if (connect(server_socket, (struct sockaddr*)&addr, sizeof(addr)) == 0) {
            cout << "서버에 연결되었습니다." << endl;
            break;
        }
    }

    pthread_t thread_id;
    if (pthread_create(&thread_id, nullptr, proc_recv, nullptr) != 0) {
        cerr << "스레드 생성 실패" << endl;
        return 1;
    }

    std::string msgBuffer;
    while (1) {
        getline(std::cin, msgBuffer); 
        ssize_t sendSize = send(server_socket, msgBuffer.c_str(), msgBuffer.size(), 0);
        if (sendSize <= 0) {
            cerr << "전송 오류" << endl;
            break;
        }
    }

    pthread_join(thread_id, nullptr);
    close(server_socket);

    return 0;
}
