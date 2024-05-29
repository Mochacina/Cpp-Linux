#include <iostream>       // ǥ�� ����� ��Ʈ���� ���� ��� ����
#include <string>         // ���ڿ� ó���� ���� ��� ����
#include <thread>         // ������ ó���� ���� ��� ����
#include <vector>         // ���� �����̳ʸ� ���� ��� ����
#include <mutex>          // ���ؽ� ����ȭ�� ���� ��� ����
#include <unordered_set>  // �ؽ� ������ ���� ��� ����
#include <asio.hpp>       // ASIO ���̺귯�� ��� ����

using asio::ip::tcp;      // ���ӽ����̽� ���� ����

class Server {
public:
    // ������: io_context ��ü�� ��Ʈ ��ȣ�� �޾Ƽ� ���� �ʱ�ȭ
    Server(asio::io_context& io_context, int port)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
        accept_connections();  // Ŭ���̾�Ʈ ���� ���� ����
    }

private:
    // Ŭ���̾�Ʈ ������ �����ϴ� �Լ�
    void accept_connections() {
        std::cout << "Server is running. Waiting for connections..." << std::endl;
        // �� ���� ����
        auto socket = std::make_shared<tcp::socket>(acceptor_.get_executor().context());
        // �񵿱������� Ŭ���̾�Ʈ ������ ����
        acceptor_.async_accept(*socket, [this, socket](std::error_code ec) {
            if (!ec) {
                // ���������� ����Ǹ� Ŭ���̾�Ʈ�� ������ ���տ� �߰�
                std::lock_guard<std::mutex> lock(mutex_);
                clients_.insert(socket);
                std::cout << "New client connected." << std::endl;
                // Ŭ���̾�Ʈ�� ó���ϴ� �����带 �����Ͽ� �񵿱������� ����
                std::thread(&Server::handle_client, this, socket).detach();
            }
            // ���� ������ �����ϱ� ���� ��������� ȣ��
            accept_connections();
        });
    }

    // Ŭ���̾�Ʈ���� ����� ó���ϴ� �Լ�
    void handle_client(std::shared_ptr<tcp::socket> socket) {
        try {
            char data[1024];  // ���� �����͸� ������ ����
            for (;;) {
                std::error_code error;
                // Ŭ���̾�Ʈ�κ��� �����͸� �񵿱������� ����
                size_t length = socket->read_some(asio::buffer(data), error);
                if (error == asio::error::eof) {
                    break; // ������ ���������� ����� ���
                } else if (error) {
                    throw asio::system_error(error); // ��Ÿ ���� �߻�
                }

                std::lock_guard<std::mutex> lock(mutex_);
                // �ٸ� ��� Ŭ���̾�Ʈ���� ���ŵ� �����͸� ����
                for (auto& client : clients_) {
                    if (client != socket) {
                        asio::write(*client, asio::buffer(data, length));
                    }
                }
            }
        } catch (std::exception& e) {
            std::cerr << "Exception in thread: " << e.what() << "\n";
        }

        // Ŭ���̾�Ʈ�� ������ ������ ���տ��� ����
        std::lock_guard<std::mutex> lock(mutex_);
        clients_.erase(socket);
        std::cout << "Client disconnected." << std::endl;
    }

    tcp::acceptor acceptor_;  // Ŭ���̾�Ʈ ������ �����ϴ� ��ü
    std::mutex mutex_;        // ��Ƽ������ ����ȭ�� ���� ���ؽ�
    std::unordered_set<std::shared_ptr<tcp::socket>> clients_;  // Ŭ���̾�Ʈ ���� ����
};

int main(int argc, char* argv[]) {
    try {
        if (argc != 2) {
            std::cerr << "Usage: server <port>\n";  // ��Ʈ ��ȣ �Է� ����
            return 1;
        }

        asio::io_context io_context;  // io_context ��ü ����
        Server s(io_context, std::atoi(argv[1]));  // ���� ��ü ���� �� �ʱ�ȭ
        io_context.run();  // io_context ����
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";  // ���� ó��
    }

    return 0;
}
