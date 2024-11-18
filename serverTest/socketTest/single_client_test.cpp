#include <iostream>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <errno.h>
#include <sys/time.h>

struct ThreadData {
    std::string ip;
    int port;
    std::string message;
    int timeout;  // n초 타임아웃
};

// 소켓 통신을 수행하는 스레드 함수
void* send_message(void* arg) {
    ThreadData* data = (ThreadData*)arg;

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Failed to create socket: " << strerror(errno) << std::endl;
        pthread_exit(NULL);
    }

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(data->port);

    if (inet_pton(AF_INET, data->ip.c_str(), &server_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address: " << data->ip << std::endl;
        close(sock);
        pthread_exit(NULL);
    }

    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Connection failed: " << strerror(errno) << std::endl;
        close(sock);
        pthread_exit(NULL);
    }

    // 메시지 전송
    ssize_t sent = send(sock, data->message.c_str(), data->message.length(), 0);
    if (sent < 0) {
        std::cerr << "Failed to send message: " << strerror(errno) << std::endl;
        close(sock);
        pthread_exit(NULL);
    } else {
        std::cout << "Message sent: " << data->message << std::endl;
    }

    // 응답 대기 또는 타임아웃 설정
    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_SET(sock, &read_fds);

    timeval timeout;
    timeout.tv_sec = data->timeout;
    timeout.tv_usec = 0;

    int select_result = select(sock + 1, &read_fds, NULL, NULL, &timeout);

    if (select_result == -1) {
        std::cerr << "Select error: " << strerror(errno) << std::endl;
    } else if (select_result == 0) {
        std::cout << "No response received within " << data->timeout << " seconds. Closing connection." << std::endl;
    } else {
        if (FD_ISSET(sock, &read_fds)) {
            char buffer[1024];
            ssize_t received = recv(sock, buffer, sizeof(buffer) - 1, 0);
            if (received > 0) {
                buffer[received] = '\0';
                std::cout << "Response received: " << buffer << std::endl;
            } else if (received == 0) {
                std::cout << "Server closed the connection." << std::endl;
            } else {
                std::cerr << "Receive error: " << strerror(errno) << std::endl;
            }
        }
    }

    close(sock);
    pthread_exit(NULL);
}

void start_thread(const std::string& ip, int port, const std::string& message, int timeout) {
    pthread_t thread;
    ThreadData* data = new ThreadData{ip, port, message, timeout};

    if (pthread_create(&thread, NULL, send_message, data) != 0) {
        std::cerr << "Failed to create thread: " << strerror(errno) << std::endl;
        delete data;
    } else {
        pthread_detach(thread);  // 스레드를 detach하여 대기하지 않음
    }
}

int main() {
    std::string server_ip;
    int server_port;
    std::string message;
    int timeout;

    // 사용자로부터 입력 받기
    std::cout << "Server IP: ";
    std::cin >> server_ip;

    std::cout << "Server Port: ";
    std::cin >> server_port;

    std::cout << "Message to send: ";
    std::cin.ignore();  // 버퍼 비우기
    std::getline(std::cin, message);

    std::cout << "Timeout (in seconds): ";
    std::cin >> timeout;

    // 스레드 시작
    start_thread(server_ip, server_port, message, timeout);

    std::cout << "Message thread started and detached." << std::endl;

    return 0;
}
