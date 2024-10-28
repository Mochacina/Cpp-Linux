#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <errno.h>
#include <chrono>
#include <thread>  // �����̸� ���� ������ ���

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

        // �޽��� ����
        ssize_t sent = send(sock, message.c_str(), message.length(), 0);
        if (sent < 0) {
            std::cerr << "Failed to send message: " << strerror(errno) << std::endl;
        } else {
            std::cout << "Message sent: " << message << std::endl;
        }

        // ���� �ݱ� (���� ����)
        close(sock);

        // m �и��� ���
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    }
}

int main() {
    std::string server_ip;
    int server_port;
    std::string message;
    int repeat_count;
    int delay_ms;

    // ����ڷκ��� �Է� �ޱ�
    std::cout << "Server IP: ";
    std::cin >> server_ip;

    std::cout << "Server Port: ";
    std::cin >> server_port;

    std::cout << "Message to send: ";
    std::cin.ignore();  // ���� ����
    std::getline(std::cin, message);

    std::cout << "Number of repetitions (n): ";
    std::cin >> repeat_count;

    std::cout << "Delay between each connection (in milliseconds, m): ";
    std::cin >> delay_ms;

    // �޽����� n�� ������ m �и��� ������
    send_message_to_server(server_ip, server_port, message, delay_ms, repeat_count);

    return 0;
}
