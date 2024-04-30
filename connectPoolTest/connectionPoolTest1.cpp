#include <iostream>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>

class DatabaseConnection {
public:
    bool connect(const char *user, const char *passwd, const char *sid) {
        EXEC SQL BEGIN DECLARE SECTION;
            varchar m_szCon_script[256];
        EXEC SQL END DECLARE SECTION;

        sprintf((char *)m_szCon_script.arr, "%s/%s@%s", user, passwd, sid);
        m_szCon_script.len = strlen((char *)m_szCon_script.arr);

        EXEC SQL CONNECT :m_szCon_script;

        if (sqlca.sqlcode != 0) {
            std::cerr << "Connection failed with SQL Code: " << sqlca.sqlcode << std::endl;
            return false;
        }
        return true;
    }

    void disconnect() {
        EXEC SQL DISCONNECT;
    }

    void executeQuery(const std::string& query) {
        std::cout << "Executing query: " << query << "\n";
    }
};

class ConnectionPool {
private:
    std::mutex mtx;
    std::condition_variable cv;
    std::queue<DatabaseConnection*> pool;

public:
    ConnectionPool(int n) {
        for (int i = 0; i < n; ++i) {
            auto conn = new DatabaseConnection();
            conn->connect();
            pool.push(conn);
        }
    }

    DatabaseConnection* getConnection() {
        std::unique_lock<std::mutex> lock(mtx);
        while (pool.empty()) {
            cv.wait(lock);
        }
        auto conn = pool.front();
        pool.pop();
        return conn;
    }

    void releaseConnection(DatabaseConnection* conn) {
        std::lock_guard<std::mutex> lock(mtx);
        pool.push(conn);
        cv.notify_one();
    }

    ~ConnectionPool() {
        while (!pool.empty()) {
            auto conn = pool.front();
            conn->disconnect();
            delete conn;
            pool.pop();
        }
    }
};

void threadFunction(ConnectionPool& pool, const std::string& query) {
    auto conn = pool.getConnection(); // 커넥션을 할당받습니다.
    if (conn) {
        conn->executeQuery(query); // 쿼리를 실행합니다.
        pool.releaseConnection(conn); // 작업이 끝난 후 커넥션을 반환합니다.
    }
}

int main() {
    ConnectionPool pool(5); // 5개의 커넥션을 갖는 풀을 생성합니다.

    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.push_back(std::thread(threadFunction, std::ref(pool), "SELECT * FROM users WHERE id = " + std::to_string(i)));
    }

    for (auto& thread : threads) {
        thread.join(); // 모든 스레드가 완료될 때까지 기다립니다.
    }

    return 0;
}
