#include <iostream>       // 표준 입출력 스트림을 위한 헤더 파일
#include <string>         // 문자열 처리를 위한 헤더 파일
#include <thread>         // 스레드 처리를 위한 헤더 파일
#include <vector>         // 벡터 컨테이너를 위한 헤더 파일
#include <mutex>          // 뮤텍스 동기화를 위한 헤더 파일
#include <unordered_set>  // 해시 집합을 위한 헤더 파일
#include <asio.hpp>       // ASIO 라이브러리 헤더 파일

using asio::ip::tcp;      // 네임스페이스 단축 선언

class Server {
public:
    // 생성자: io_context 객체와 포트 번호를 받아서 서버 초기화
    Server(asio::io_context& io_context, int port)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
        accept_connections();  // 클라이언트 연결 수락 시작
    }

private:
    // 클라이언트 연결을 수락하는 함수
    void accept_connections() {
        std::cout << "Server is running. Waiting for connections..." << std::endl;
        // 새 소켓 생성
        auto socket = std::make_shared<tcp::socket>(acceptor_.get_executor().context());
        // 비동기적으로 클라이언트 연결을 수락
        acceptor_.async_accept(*socket, [this, socket](std::error_code ec) {
            if (!ec) {
                // 성공적으로 연결되면 클라이언트를 관리할 집합에 추가
                std::lock_guard<std::mutex> lock(mutex_);
                clients_.insert(socket);
                std::cout << "New client connected." << std::endl;
                // 클라이언트를 처리하는 스레드를 생성하여 비동기적으로 실행
                std::thread(&Server::handle_client, this, socket).detach();
            }
            // 다음 연결을 수락하기 위해 재귀적으로 호출
            accept_connections();
        });
    }

    // 클라이언트와의 통신을 처리하는 함수
    void handle_client(std::shared_ptr<tcp::socket> socket) {
        try {
            char data[1024];  // 수신 데이터를 저장할 버퍼
            for (;;) {
                std::error_code error;
                // 클라이언트로부터 데이터를 비동기적으로 읽음
                size_t length = socket->read_some(asio::buffer(data), error);
                if (error == asio::error::eof) {
                    break; // 연결이 정상적으로 종료된 경우
                } else if (error) {
                    throw asio::system_error(error); // 기타 오류 발생
                }

                std::lock_guard<std::mutex> lock(mutex_);
                // 다른 모든 클라이언트에게 수신된 데이터를 전송
                for (auto& client : clients_) {
                    if (client != socket) {
                        asio::write(*client, asio::buffer(data, length));
                    }
                }
            }
        } catch (std::exception& e) {
            std::cerr << "Exception in thread: " << e.what() << "\n";
        }

        // 클라이언트가 연결을 끊으면 집합에서 제거
        std::lock_guard<std::mutex> lock(mutex_);
        clients_.erase(socket);
        std::cout << "Client disconnected." << std::endl;
    }

    tcp::acceptor acceptor_;  // 클라이언트 연결을 수락하는 객체
    std::mutex mutex_;        // 멀티스레드 동기화를 위한 뮤텍스
    std::unordered_set<std::shared_ptr<tcp::socket>> clients_;  // 클라이언트 소켓 집합
};

int main(int argc, char* argv[]) {
    try {
        if (argc != 2) {
            std::cerr << "Usage: server <port>\n";  // 포트 번호 입력 유도
            return 1;
        }

        asio::io_context io_context;  // io_context 객체 생성
        Server s(io_context, std::atoi(argv[1]));  // 서버 객체 생성 및 초기화
        io_context.run();  // io_context 실행
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";  // 예외 처리
    }

    return 0;
}
