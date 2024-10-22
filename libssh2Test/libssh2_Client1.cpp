#include <libssh2.h>
#include <libssh2_sftp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>

void list_files(LIBSSH2_SFTP *sftp_session, const char *path);
void download_file(LIBSSH2_SFTP *sftp_session, const char *remote_file);
void upload_file(LIBSSH2_SFTP *sftp_session, const char *local_file);

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <IP> <Port>\n", argv[0]);
        return 1;
    }

    const char *hostname = argv[1];
    int port = atoi(argv[2]);
    const char *username = "sftpuser";  // 사용자 이름
    const char *password = "1234";  // 비밀번호

    int sock;
    struct sockaddr_in sin;
    LIBSSH2_SESSION *session;
    LIBSSH2_SFTP *sftp_session;
    int rc;

    // libssh2 초기화
    rc = libssh2_init(0);
    if (rc != 0) {
        fprintf(stderr, "libssh2 초기화 실패\n");
        return 1;
    }

    // 소켓 생성 및 서버 연결
    sock = socket(AF_INET, SOCK_STREAM, 0);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = inet_addr(hostname);
    if (connect(sock, (struct sockaddr *)(&sin), sizeof(struct sockaddr_in)) != 0) {
        fprintf(stderr, "서버 연결 실패\n");
        return 1;
    }

    // SSH 세션 생성 및 핸드쉐이크
    session = libssh2_session_init();
    if (libssh2_session_handshake(session, sock)) {
        fprintf(stderr, "SSH 핸드쉐이크 실패\n");
        return 1;
    }

    // 사용자 인증
    if (libssh2_userauth_password(session, username, password)) {
        fprintf(stderr, "사용자 인증 실패\n");
        return 1;
    }

    // SFTP 세션 생성
    sftp_session = libssh2_sftp_init(session);
    if (!sftp_session) {
        fprintf(stderr, "SFTP 세션 생성 실패\n");
        return 1;
    }

    // 기본 경로 파일 리스트 출력
    list_files(sftp_session, ".");

    // 명령어 입력 루프
    char command[256];
    while (1) {
        printf("sftp> ");
        fgets(command, sizeof(command), stdin);
        command[strlen(command) - 1] = '\0';  // 줄바꿈 제거

        // 경로 이동
        if (strncmp(command, "cd ", 3) == 0) {
            const char *path = command + 3;
            list_files(sftp_session, path);
        }
        // 파일 다운로드
        else if (strncmp(command, "down ", 5) == 0) {
            const char *remote_file = command + 5;
            download_file(sftp_session, remote_file);
        }
        // 파일 업로드
        else if (strncmp(command, "up ", 3) == 0) {
            const char *local_file = command + 3;
            upload_file(sftp_session, local_file);
        }
        // 종료
        else if (strcmp(command, "exit") == 0) {
            break;
        }
        else {
            printf("Unknown command: %s\n", command);
        }
    }

    // 세션 종료
    libssh2_sftp_shutdown(sftp_session);
    libssh2_session_disconnect(session, "Normal Shutdown");
    libssh2_session_free(session);
    close(sock);
    libssh2_exit();

    return 0;
}

// 파일 리스트 출력 함수
void list_files(LIBSSH2_SFTP *sftp_session, const char *path) {
    LIBSSH2_SFTP_HANDLE *sftp_handle = libssh2_sftp_opendir(sftp_session, path);
    if (!sftp_handle) {
        fprintf(stderr, "디렉토리 열기 실패: %s\n", path);
        return;
    }

    char mem[512];
    LIBSSH2_SFTP_ATTRIBUTES attrs;

    printf("디렉토리 리스트: %s\n", path);
    while (libssh2_sftp_readdir(sftp_handle, mem, sizeof(mem), &attrs) > 0) {
        printf("%s\n", mem);
    }

    libssh2_sftp_closedir(sftp_handle);
}

// 파일 다운로드 함수
void download_file(LIBSSH2_SFTP *sftp_session, const char *remote_file) {
    LIBSSH2_SFTP_HANDLE *sftp_handle = libssh2_sftp_open(sftp_session, remote_file, LIBSSH2_FXF_READ, 0);
    if (!sftp_handle) {
        fprintf(stderr, "원격 파일 열기 실패: %s\n", remote_file);
        return;
    }

    FILE *local_file = fopen(remote_file, "wb");
    if (!local_file) {
        fprintf(stderr, "로컬 파일 열기 실패: %s\n", remote_file);
        return;
    }

    char buffer[1024];
    ssize_t nread;
    while ((nread = libssh2_sftp_read(sftp_handle, buffer, sizeof(buffer))) > 0) {
        fwrite(buffer, 1, nread, local_file);
    }

    fclose(local_file);
    libssh2_sftp_close(sftp_handle);
    printf("파일 다운로드 완료: %s\n", remote_file);
}

// 파일 업로드 함수
void upload_file(LIBSSH2_SFTP *sftp_session, const char *local_file) {
    LIBSSH2_SFTP_HANDLE *sftp_handle = libssh2_sftp_open(sftp_session, local_file, LIBSSH2_FXF_WRITE | LIBSSH2_FXF_CREAT | LIBSSH2_FXF_TRUNC, LIBSSH2_SFTP_S_IRUSR | LIBSSH2_SFTP_S_IWUSR | LIBSSH2_SFTP_S_IRGRP | LIBSSH2_SFTP_S_IROTH);
    if (!sftp_handle) {
        fprintf(stderr, "원격 파일 열기 실패: %s\n", local_file);
        return;
    }

    FILE *file = fopen(local_file, "rb");
    if (!file) {
        fprintf(stderr, "로컬 파일 열기 실패: %s\n", local_file);
        return;
    }

    char buffer[1024];
    size_t nread;
    while ((nread = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        libssh2_sftp_write(sftp_handle, buffer, nread);
    }

    fclose(file);
    libssh2_sftp_close(sftp_handle);
    printf("파일 업로드 완료: %s\n", local_file);
}
