#include "./libssh2-1.11.0/include/libssh2.h"
#include "./libssh2-1.11.0/include/libssh2_sftp.h"

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

    // Clean up and exit
    libssh2_sftp_shutdown(sftp_session);
    libssh2_session_disconnect(session, "Normal shutdown");
    libssh2_session_free(session);
    libssh2_exit();

    return 0;
}
