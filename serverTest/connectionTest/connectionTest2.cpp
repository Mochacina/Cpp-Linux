#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <errno.h>
#include <chrono>
#include <thread>  // 딜레이를 위한 스레드 사용

void send_message_to_server(const std::string& ip, int port, const std::string& message, int delay_ms, int repeat_count) {
    for (int i = 0; i < repeat_count; ++i) {
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            std::cerr << "Failed to create socket: " << strerror(errno) << std::endl;
            return;
        }

        sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);

        if (inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr) <= 0) {
            std::cerr << "Invalid address: " << ip << std::endl;
            close(sock);
            return;
        }

        if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
            std::cerr << "Connection failed: " << strerror(errno) << std::endl;
            close(sock);
            return;
        }

        // 메시지 전송
        ssize_t sent = send(sock, message.c_str(), message.length(), 0);
        if (sent < 0) {
            std::cerr << "Failed to send message: " << strerror(errno) << std::endl;
        } else {
            std::cout << "Message sent: " << message << std::endl;
        }

        // 소켓 닫기 (연결 끊기)
        close(sock);

        // m 밀리초 대기
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    }
}

int main() {
    std::string server_ip;
    int server_port;
    std::string message;
    int repeat_count;
    int delay_ms;

    // 사용자로부터 입력 받기
    std::cout << "Server IP: ";
    std::cin >> server_ip;

    std::cout << "Server Port: ";
    std::cin >> server_port;

    std::cout << "Message to send: ";
    std::cin.ignore();  // 버퍼 비우기
    std::getline(std::cin, message);

    std::cout << "Number of repetitions (n): ";
    std::cin >> repeat_count;

    std::cout << "Delay between each connection (in milliseconds, m): ";
    std::cin >> delay_ms;

    // 메시지를 n번 보내고 m 밀리초 딜레이
    send_message_to_server(server_ip, server_port, message, delay_ms, repeat_count);

    return 0;
}
