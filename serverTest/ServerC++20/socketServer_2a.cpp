#include <iostream>      // 표준 입출력 라이브러리
#include <thread>        // 스레드 라이브러리
#include <vector>        // 벡터 컨테이너 라이브러리
#include <mutex>         // 뮤텍스 라이브러리
#include <unordered_map> // 해시 맵 컨테이너 라이브러리
#include <string>        // 문자열 라이브러리
#include <algorithm>     // 알고리즘 라이브러리
#include <cstring>       // C 스타일 문자열 처리 라이브러리
#include <netinet/in.h>  // 소켓 통신을 위한 라이브러리
#include <unistd.h>      // UNIX 표준 함수 라이브러리

// 버퍼 크기 상수 정의
constexpr int BUFFER_SIZE = 1024;

// 클라이언트 소켓과 해당 스레드를 저장할 맵
std::unordered_map<int, std::thread> clients;
// 클라이언트 맵의 스레드 안전성을 위한 뮤텍스
std::mutex clients_mutex;

// 메시지를 모든 클라이언트에게 브로드캐스트하는 함수
void broadcast_message(const std::string &message, int sender_fd) {
    // 뮤텍스를 사용하여 클라이언트 맵 접근 동기화
    std::lock_guard<std::mutex> lock(clients_mutex);
    for (const auto &client : clients) {
        // 메시지를 보낸 클라이언트는 제외
        if (client.first != sender_fd) {
            send(client.first, message.c_str(), message.size(), 0);
        }
    }
}

// 각 클라이언트를 처리하는 함수
void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    while (true) {
        std::memset(buffer, 0, BUFFER_SIZE); // 버퍼 초기화
        int bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0); // 메시지 수신
        if (bytes_received <= 0) {
            std::cerr << "Client disconnected or error occurred" << std::endl;
            break; // 연결 종료 또는 에러 발생 시 루프 종료
        }
        // 수신된 메시지 포맷팅
        std::string message = "Client " + std::to_string(client_socket) + ": " + buffer;
        std::cout << message;
        broadcast_message(message, client_socket); // 메시지 브로드캐스트
    }

    // 클라이언트가 연결 종료 시 맵에서 제거하고 소켓 닫기
    std::lock_guard<std::mutex> lock(clients_mutex);
    clients.erase(client_socket);
    close(client_socket);
}

// 메인 함수
int main(int argc, char* argv[]) {
    // 포트 번호를 인자로 받으며 그렇지 못한 경우 종료
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <port_number>" << std::endl;
        return 1;
    }

    // 입력받은 포트 번호를 정수로 변환
    int port = std::stoi(argv[1]);

    // 서버 소켓 생성
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    // 서버 주소 정보 설정
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;              // IPv4
    server_address.sin_addr.s_addr = INADDR_ANY;      // 모든 IP 주소에서 수신
    server_address.sin_port = htons(port);            // 포트 번호 설정

    // 소켓과 주소 바인딩
    if (bind(server_socket, reinterpret_cast<sockaddr*>(&server_address), sizeof(server_address)) == -1) {
        std::cerr << "Failed to bind to address" << std::endl;
        close(server_socket);
        return 1;
    }

    // 연결 요청 대기
    if (listen(server_socket, SOMAXCONN) == -1) {
        std::cerr << "Failed to listen on socket" << std::endl;
        close(server_socket);
        return 1;
    }

    std::cout << "Server is listening on port " << port << std::endl;

    while (true) {
        sockaddr_in client_address;
        socklen_t client_size = sizeof(client_address);
        // 클라이언트 연결 수락
        int client_socket = accept(server_socket, reinterpret_cast<sockaddr*>(&client_address), &client_size);
        if (client_socket == -1) {
            std::cerr << "Failed to accept client connection" << std::endl;
            continue;
        }

        // 클라이언트 소켓을 맵에 추가하고 스레드 생성
        std::lock_guard<std::mutex> lock(clients_mutex);
        clients[client_socket] = std::thread(handle_client, client_socket);
        // 스레드를 분리하여 독립적으로 실행되도록 설정
        clients[client_socket].detach();
        std::cout << "Client " << client_socket << " connected" << std::endl;
    }

    // 서버 소켓 닫기 (이 코드는 실행되지 않지만 안전을 위해 추가)
    close(server_socket);
    return 0;
}
