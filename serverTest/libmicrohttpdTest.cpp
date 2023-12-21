#include <microhttpd.h>
#include <string.h>

#define PORT 8080

int hello_handler(void *cls, struct MHD_Connection *connection, const char *url, const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls) {
    const char *hello_response = "Hello, this is a RESTful server!";

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(hello_response), (void *)hello_response, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL, &hello_handler, NULL, MHD_OPTION_END);
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
