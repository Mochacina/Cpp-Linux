#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <poll.h>
#include <cstring>
#include <vector>

#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

int main() {
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("Socket creation failed");
        return 1;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_sock);
        return 1;
    }

    if (listen(server_sock, MAX_CLIENTS) < 0) {
        perror("Listen failed");
        close(server_sock);
        return 1;
    }

    std::vector<pollfd> poll_fds;
    pollfd server_pollfd{server_sock, POLLIN, 0};
    poll_fds.push_back(server_pollfd);

    char buffer[BUFFER_SIZE];

    while (true) {
        int event_count = poll(poll_fds.data(), poll_fds.size(), -1);  // 무한 대기
        if (event_count < 0) {
            perror("poll failed");
            break;
        }

        for (auto it = poll_fds.begin(); it != poll_fds.end();) {
            if (it->revents & POLLIN) {
                if (it->fd == server_sock) {
                    // 새 클라이언트 연결 처리
                    sockaddr_in client_addr{};
                    socklen_t client_len = sizeof(client_addr);
                    int client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_len);
                    if (client_sock >= 0) {
                        pollfd client_pollfd{client_sock, POLLIN, 0};
                        poll_fds.push_back(client_pollfd);
                        std::cout << "New client connected: " << client_sock << std::endl;
                    }
                } else {
                    // 클라이언트에서 데이터 수신
                    ssize_t bytes_read = recv(it->fd, buffer, sizeof(buffer) - 1, 0);
                    if (bytes_read <= 0) {
                        // 연결 종료
                        std::cout << "Client disconnected: " << it->fd << std::endl;
                        close(it->fd);
                        it = poll_fds.erase(it);
                        continue;
                    } else {
                        buffer[bytes_read] = '\0';
                        std::cout << "Received from client " << it->fd << ": " << buffer << std::endl;
                    }
                }
            }
            ++it;
        }
    }

    close(server_sock);
    return 0;
}
