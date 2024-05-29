#include <iostream>      // ǥ�� ����� ���̺귯��
#include <thread>        // ������ ���̺귯��
#include <vector>        // ���� �����̳� ���̺귯��
#include <mutex>         // ���ؽ� ���̺귯��
#include <unordered_map> // �ؽ� �� �����̳� ���̺귯��
#include <string>        // ���ڿ� ���̺귯��
#include <algorithm>     // �˰��� ���̺귯��
#include <cstring>       // C ��Ÿ�� ���ڿ� ó�� ���̺귯��
#include <netinet/in.h>  // ���� ����� ���� ���̺귯��
#include <unistd.h>      // UNIX ǥ�� �Լ� ���̺귯��

// ���� ũ�� ��� ����
constexpr int BUFFER_SIZE = 1024;

// Ŭ���̾�Ʈ ���ϰ� �ش� �����带 ������ ��
std::unordered_map<int, std::thread> clients;
// Ŭ���̾�Ʈ ���� ������ �������� ���� ���ؽ�
std::mutex clients_mutex;

// �޽����� ��� Ŭ���̾�Ʈ���� ��ε�ĳ��Ʈ�ϴ� �Լ�
void broadcast_message(const std::string &message, int sender_fd) {
    // ���ؽ��� ����Ͽ� Ŭ���̾�Ʈ �� ���� ����ȭ
    std::lock_guard<std::mutex> lock(clients_mutex);
    for (const auto &client : clients) {
        // �޽����� ���� Ŭ���̾�Ʈ�� ����
        if (client.first != sender_fd) {
            send(client.first, message.c_str(), message.size(), 0);
        }
    }
}

// �� Ŭ���̾�Ʈ�� ó���ϴ� �Լ�
void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    while (true) {
        std::memset(buffer, 0, BUFFER_SIZE); // ���� �ʱ�ȭ
        int bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0); // �޽��� ����
        if (bytes_received <= 0) {
            std::cerr << "Client disconnected or error occurred" << std::endl;
            break; // ���� ���� �Ǵ� ���� �߻� �� ���� ����
        }
        // ���ŵ� �޽��� ������
        std::string message = "Client " + std::to_string(client_socket) + ": " + buffer;
        std::cout << message;
        broadcast_message(message, client_socket); // �޽��� ��ε�ĳ��Ʈ
    }

    // Ŭ���̾�Ʈ�� ���� ���� �� �ʿ��� �����ϰ� ���� �ݱ�
    std::lock_guard<std::mutex> lock(clients_mutex);
    clients.erase(client_socket);
    close(client_socket);
}

// ���� �Լ�
int main(int argc, char* argv[]) {
    // ��Ʈ ��ȣ�� ���ڷ� ������ �׷��� ���� ��� ����
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <port_number>" << std::endl;
        return 1;
    }

    // �Է¹��� ��Ʈ ��ȣ�� ������ ��ȯ
    int port = std::stoi(argv[1]);

    // ���� ���� ����
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    // ���� �ּ� ���� ����
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;              // IPv4
    server_address.sin_addr.s_addr = INADDR_ANY;      // ��� IP �ּҿ��� ����
    server_address.sin_port = htons(port);            // ��Ʈ ��ȣ ����

    // ���ϰ� �ּ� ���ε�
    if (bind(server_socket, reinterpret_cast<sockaddr*>(&server_address), sizeof(server_address)) == -1) {
        std::cerr << "Failed to bind to address" << std::endl;
        close(server_socket);
        return 1;
    }

    // ���� ��û ���
    if (listen(server_socket, SOMAXCONN) == -1) {
        std::cerr << "Failed to listen on socket" << std::endl;
        close(server_socket);
        return 1;
    }

    std::cout << "Server is listening on port " << port << std::endl;

    while (true) {
        sockaddr_in client_address;
        socklen_t client_size = sizeof(client_address);
        // Ŭ���̾�Ʈ ���� ����
        int client_socket = accept(server_socket, reinterpret_cast<sockaddr*>(&client_address), &client_size);
        if (client_socket == -1) {
            std::cerr << "Failed to accept client connection" << std::endl;
            continue;
        }

        // Ŭ���̾�Ʈ ������ �ʿ� �߰��ϰ� ������ ����
        std::lock_guard<std::mutex> lock(clients_mutex);
        clients[client_socket] = std::thread(handle_client, client_socket);
        // �����带 �и��Ͽ� ���������� ����ǵ��� ����
        clients[client_socket].detach();
        std::cout << "Client " << client_socket << " connected" << std::endl;
    }

    // ���� ���� �ݱ� (�� �ڵ�� ������� ������ ������ ���� �߰�)
    close(server_socket);
    return 0;
}
