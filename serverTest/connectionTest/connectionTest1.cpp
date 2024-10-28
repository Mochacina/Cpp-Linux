#include <iostream>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <errno.h>
#include <sys/time.h>  // gettimeofday 사용

struct ThreadData {
    std::string ip;
    int port;
    int connection_id;
    int duration_s;  // z초 후에 연결 종료
};

// 현재 시간을 초 단위로 반환하는 함수
long get_current_time_in_seconds() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec;
}

// 스레드에서 실행할 함수
void* connect_to_server(void* arg) {
    ThreadData* data = (ThreadData*)arg;

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Failed to create socket for connection " << data->connection_id << std::endl;
        pthread_exit(NULL);
    }

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(data->port);

    if (inet_pton(AF_INET, data->ip.c_str(), &server_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address for connection " << data->connection_id << std::endl;
        close(sock);
        pthread_exit(NULL);
    }

    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Connection failed for connection " << data->connection_id << ": " << strerror(errno) << std::endl;
        close(sock);
        pthread_exit(NULL);
    }

    std::cout << "Connection " << data->connection_id << " established with server" << std::endl;

    // 시작 시간을 기록
    long start_time = get_current_time_in_seconds();
    
    // z초 동안 연결 유지
    while (true) {
        long current_time = get_current_time_in_seconds();
        
        if (current_time - start_time >= data->duration_s) {
            std::cout << "Connection " << data->connection_id << " closing after " << data->duration_s << " seconds" << std::endl;
            break;
        }
        usleep(1000000);  // 1초 대기
    }

    close(sock);
    pthread_exit(NULL);
}

int main() {
    std::string server_ip;
    int server_port;
    int n_connections;
    int interval_us;
    int duration_s;

    // 사용자로부터 입력 받기
    std::cout << "Server IP: ";
    std::cin >> server_ip;

    std::cout << "Server Port: ";
    std::cin >> server_port;

    std::cout << "Number of Connections (n): ";
    std::cin >> n_connections;

    std::cout << "Interval between connection creation (in microseconds, m): ";
    std::cin >> interval_us;

    std::cout << "Duration for each connection (in seconds, z): ";
    std::cin >> duration_s;

    // 스레드와 데이터 구조체 배열 생성
    pthread_t threads[n_connections];
    ThreadData thread_data[n_connections];

    // n개의 스레드 생성
    for (int i = 0; i < n_connections; ++i) {
        thread_data[i].ip = server_ip;
        thread_data[i].port = server_port;
        thread_data[i].connection_id = i + 1;
        thread_data[i].duration_s = duration_s;

        if (pthread_create(&threads[i], NULL, connect_to_server, &thread_data[i]) != 0) {
            std::cerr << "Failed to create thread for connection " << i + 1 << std::endl;
            return 1;
        }

        // 스레드 생성 주기적으로 기다림 (m 마이크로초 대기)
        usleep(interval_us);
    }

    // 모든 스레드가 종료될 때까지 대기
    for (int i = 0; i < n_connections; ++i) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}