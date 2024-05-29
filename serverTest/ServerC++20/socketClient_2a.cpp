#include <iostream>
#include <thread>
#include <string>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

constexpr int BUFFER_SIZE = 1024;

// �����κ��� �޽����� �����ϴ� �Լ�
void receive_messages(int client_socket) {
    char buffer[BUFFER_SIZE];
    while (true) {
        std::memset(buffer, 0, BUFFER_SIZE);
        int bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_received <= 0) {
            std::cerr << "Server disconnected or error occurred" << std::endl;
            break;
        }
        std::cout << "Server: " << buffer << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <server_ip> <port_number>" << std::endl;
        return 1;
    }

    const char* server_ip = argv[1];
    int port = std::stoi(argv[2]);

    // Ŭ���̾�Ʈ ���� ����
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    // ���� �ּ� ����
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    if (inet_pton(AF_INET, server_ip, &server_address.sin_addr) <= 0) {
        std::cerr << "Invalid address or address not supported" << std::endl;
        close(client_socket);
        return 1;
    }

    // ������ ����
    if (connect(client_socket, reinterpret_cast<sockaddr*>(&server_address), sizeof(server_address)) == -1) {
        std::cerr << "Connection to the server failed" << std::endl;
        close(client_socket);
        return 1;
    }

    std::cout << "Connected to the server" << std::endl;

    // �����κ��� �޽����� �����ϴ� ������ ����
    std::thread receive_thread(receive_messages, client_socket);
    receive_thread.detach();

    // ����� �Է��� ������ ����
    std::string message;
    while (true) {
        std::getline(std::cin, message);
        if (message == "/quit") {
            break;
        }
        send(client_socket, message.c_str(), message.size(), 0);
    }

    // ���� �ݱ�
    close(client_socket);
    return 0;
}