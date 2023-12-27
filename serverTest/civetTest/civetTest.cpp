#include "CivetServer.h"

class HelloWorldHandler : public CivetHandler {
public:
    bool handleGet(CivetServer *server, struct mg_connection *conn) {
        mg_printf(conn, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n");
        mg_printf(conn, "Hello, World!");
        return true;
    }
};

int main() {
    const char *options[] = {"listening_ports", "8888", nullptr};
    CivetServer server(options);

    server.addHandler("/hello", new HelloWorldHandler());

    printf("Server started on port 8888\n");
    getchar(); // Press Enter to stop the server

    delete *options;

    return 0;
}
