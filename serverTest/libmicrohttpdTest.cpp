#include <microhttpd.h>
#include <string.h>
#include <cstdio>

#define PORT 8080

int request_handler(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **con_cls)
                                {
    // 특정 경로에 따라 다르게 처리
    if (strcmp(url, "/hello") == 0) {
        const char *page = "<html><body>Hello, World!</body></html>";
        struct MHD_Response *response;
        int ret;

        response = MHD_create_response_from_buffer(strlen(page), (void *)page,
                                                   MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);

        return ret;
    }

    // 파라미터를 받아 처리
    if (strcmp(url, "/echo") == 0 && strcmp(method, "GET") == 0) {
        const char *value = MHD_lookup_connection_value(connection,
                                                         MHD_GET_ARGUMENT_KIND,
                                                         "param");

        if (value != NULL) {
            struct MHD_Response *response;
            int ret;
            char *page;

            // 받은 파라미터를 페이지에 표시
            asprintf(&page, "<html><body>Parameter: %s</body></html>", value);

            response = MHD_create_response_from_buffer(strlen(page), (void *)page,
                                                       MHD_RESPMEM_PERSISTENT);
            ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
            MHD_destroy_response(response);
            
            delete page;

            return ret;
        }
    }

    // 정의되지 않은 경로에 대한 기본 응답
    const char *not_found_page = "<html><body>Not Found</body></html>";
    struct MHD_Response *not_found_response = MHD_create_response_from_buffer(
        strlen(not_found_page), (void *)not_found_page, MHD_RESPMEM_PERSISTENT);

    return MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, not_found_response);
}

// int bye_handler(void *cls, struct MHD_Connection *connection, const char *url, const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls) {
//     const char *bye_response = "Goodbye, this is the bye endpoint!";

//     struct MHD_Response *response = MHD_create_response_from_buffer(strlen(bye_response), (void *)bye_response, MHD_RESPMEM_PERSISTENT);
//     int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
//     MHD_destroy_response(response);

//     return ret;
// }

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL, &request_handler, NULL, MHD_OPTION_END);
    if (NULL == daemon) {
        fprintf(stderr, "Failed to start the server\n");
        return 1;
    }

    printf("Server is running on http://localhost:%d\n", PORT);
    printf("Press Enter to stop the server\n");
    getchar(); // Press Enter to stop the server

    MHD_stop_daemon(daemon);

    return 0;
}
