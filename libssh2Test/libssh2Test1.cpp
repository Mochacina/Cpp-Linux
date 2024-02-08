#include "./libssh2-1.11.0/include/libssh2.h"
#include "./libssh2-1.11.0/include/libssh2_sftp.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <vector>
#include <cstring>
#include <string>

#include <iostream>

int main() {
    // Initialize libssh2
    int rc = libssh2_init(0);
    if (rc != 0) {
        // Handle initialization error
        return rc;
    }

    // Create a new SSH session
    LIBSSH2_SESSION *session = libssh2_session_init();
    if (!session) {
        // Handle session creation error
        libssh2_exit();
        return -1;
    }

    // Set up socket and connect to SSH server
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        // Handle socket creation error
        return -1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(22);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int rc = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (rc != 0) {
        // Handle connection error
        close(sockfd);
        return -1;
    }

    // Set up the SSH session options
    libssh2_session_set_blocking(session, 1);
    libssh2_session_handshake(session, sockfd);

    // Authenticate the SSH session
    libssh2_userauth_password(session, "username", "password");

    // Open an SFTP session
    LIBSSH2_SFTP *sftp_session = libssh2_sftp_init(session);
    if (!sftp_session) {
        // Handle SFTP session creation error
        libssh2_session_disconnect(session, "Failed to initialize SFTP session");
        libssh2_session_free(session);
        libssh2_exit();
        return -1;
    }

    // Perform SFTP operations
    LIBSSH2_SFTP_HANDLE *sftp_handle = libssh2_sftp_open(sftp_session, "/home/username/test.txt", LIBSSH2_FXF_READ, 0);
    if (!sftp_handle) {
        // Handle file open error
        libssh2_sftp_shutdown(sftp_session);
        libssh2_session_disconnect(session, "Failed to open file");
        libssh2_session_free(session);
        libssh2_exit();
        return -1;
    }

    char buffer[1024];
    ssize_t bytes_read = libssh2_sftp_read(sftp_handle, buffer, sizeof(buffer));
    if (bytes_read < 0) {
        // Handle file read error
        libssh2_sftp_close(sftp_handle);
        libssh2_sftp_shutdown(sftp_session);
        libssh2_session_disconnect(session, "Failed to read from file");
        libssh2_session_free(session);
        libssh2_exit();
        return -1;
    }

    // Print the contents of the file
    std::cout << std::string(buffer, bytes_read) << std::endl;

    // Close the file and disconnect from the SFTP session
    libssh2_sftp_close(sftp_handle);
    libssh2_sftp_shutdown(sftp_session);

    // Clean up and exit
    libssh2_sftp_shutdown(sftp_session);
    libssh2_session_disconnect(session, "Normal shutdown");
    libssh2_session_free(session);
    libssh2_exit();

    return 0;
}
