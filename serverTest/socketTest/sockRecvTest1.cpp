#include <iostream>
#include <string>
#include <sys/socket.h> // ���� ���� �Լ��� ����ϱ� ���� ��� ����

int main() {
    int sockfd; // ���� ���� ��ũ����
    // sockfd �ʱ�ȭ�� ���� ������ ����

    const int buffer_size = 1024; // ���� ũ�⸦ ����
    char buffer[buffer_size]; // �����͸� ���� ����

    // recv �Լ��� ����Ͽ� ������ ����
    int bytes_received = recv(sockfd, buffer, buffer_size - 1, 0);
    if (bytes_received < 0) {
        std::cerr << "recv() failed" << std::endl;
        return 1;
    } else if (bytes_received == 0) {
        std::cout << "Connection closed by peer" << std::endl;
        return 0;
    }

    // ���� �������� ���� �� ���� �߰�
    buffer[bytes_received] = '\0';

    // std::string ��ü ����
    std::string received_data(buffer);

    // ���ŵ� ������ ���
    std::cout << "Received: " << received_data << std::endl;

    return 0;
}
