#include <iostream>
#include <string>
#include <sys/socket.h> // 소켓 관련 함수를 사용하기 위한 헤더 파일

int main() {
    int sockfd; // 소켓 파일 디스크립터
    // sockfd 초기화와 연결 설정은 생략

    const int buffer_size = 1024; // 버퍼 크기를 정의
    char buffer[buffer_size]; // 데이터를 받을 버퍼

    // recv 함수를 사용하여 데이터 수신
    int bytes_received = recv(sockfd, buffer, buffer_size - 1, 0);
    if (bytes_received < 0) {
        std::cerr << "recv() failed" << std::endl;
        return 1;
    } else if (bytes_received == 0) {
        std::cout << "Connection closed by peer" << std::endl;
        return 0;
    }

    // 받은 데이터의 끝에 널 문자 추가
    buffer[bytes_received] = '\0';

    // std::string 객체 생성
    std::string received_data(buffer);

    // 수신된 데이터 출력
    std::cout << "Received: " << received_data << std::endl;

    return 0;
}
