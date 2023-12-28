#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <netdb.h>
#include <netinet/in.h>
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include "http-parser.h"

using namespace std;

static void s_handle_client(int client_sock, struct sockaddr_in * client_addr, socklen_t client_addr_len);

int main(int argc, char *args[]) {

	int sock;
	int client;
	struct sockaddr_in addr;
	struct sockaddr_in client_addr;
	socklen_t addr_len = sizeof(addr);
	int bind_port = 8080;
	int on = 1;

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock < 0) {
		perror("socket() error");
		return 1;
	}
	
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (void*)&on, sizeof(on)) != 0) {
		perror("setsockopt() error");
		return 1;
	}

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(bind_port);
	if (bind(sock, (struct sockaddr*)&addr, addr_len) != 0) {
		perror("bind() error");
		return 1;
	}

	if (listen(sock, 5) != 0) {
		perror("listen() error");
		return 1;
	}

	printf("listening... %d\n", bind_port);
	while (1) {
		client = accept(sock, (struct sockaddr*)&client_addr, &addr_len);
		if (client < 0) {
			perror("accept() error");
			return 1;
		}

		s_handle_client(client, &client_addr, addr_len);
	}
	
	close(sock);
	
    return 0;
}

/*
unordered_map<string, string> parseQueryString(const string& queryString) {
    // 결과를 저장할 unordered_map 선언
	unordered_map<string, string> params;

	// 입력 문자열을 istringstream을 사용하여 스트림으로 변환
    istringstream iss(queryString);

	// '&'을 구분자로 사용하여 문자열을 분리하고 반복
    string param;
    while (getline(iss, param, '&')) {
        size_t equalPos = param.find('=');
        if (equalPos != string::npos) {
			// 키와 값 추출하여 map에 저장
            string key = param.substr(0, equalPos);
            string value = param.substr(equalPos + 1);
            params[key] = value;
        } 
    }

    return params;
}

// URL의 경로와 매개변수 파싱 함수
void parsePathAndParameters(const string& url) {
    size_t questionMarkPos = url.find('?');
    string path = (questionMarkPos != string::npos) ? url.substr(0, questionMarkPos) : url;
    string queryString = (questionMarkPos != string::npos) ? url.substr(questionMarkPos + 1) : "";

    cout << "Path: " << path << endl;

    // 쿼리 스트링 파싱
    unordered_map<string, string> params = parseQueryString(queryString);

    // 파싱된 매개변수 출력
    std::cout << "Parameters:" << std::endl;
    for (const auto& param : params) {
        std::cout << param.first << " = " << param.second << std::endl;
    }
}
*/


static void s_handle_client(int client_sock, struct sockaddr_in * client_addr, socklen_t client_addr_len) {
	int read_len = -1;
	char header_buffer[2048] = {0,};
	size_t p = 0;
	http_request_line_t request = {0,};
	http_header_fields_t fields = {0,};
	char response_header[4096] = {0,};
	char response_content[4096] = {0,};
	char client_ip_address[128] = {0,};

	while (p < sizeof(header_buffer) && (read_len = recv(client_sock, header_buffer + p, 1, 0)) > 0) {
		if (p > 4 &&
			header_buffer[p - 3] == '\r' && header_buffer[p - 2] == '\n' &&
			header_buffer[p - 1] == '\r' && header_buffer[p] == '\n') {
			break;
		}
		p++;
		read_len = -1;
	}

	if (read_len < 0) {
		printf("socket closed\n");
		return;
	}

	inet_ntop(client_addr->sin_family, &client_addr->sin_addr, client_ip_address, sizeof(client_ip_address));
	
	parseHttpHeader(parseHttpRequestLine(header_buffer, &request), &fields);

	snprintf(response_header, sizeof(response_header), "HTTP/1.1 200 OK\r\n"
			 "Content-Type: text/html\r\n"
			 "Content-Length: %ld\r\n"
			 "\r\n", strlen(response_content));

	snprintf(response_content, sizeof(response_content), "<h1>Your Request Information</h1>"
			 "<p>You IP Address: %s:%d</p>"
			 "<ul>"
			 "<li>Method: %s</li>"
			 "<li>Path: %s</li>"
			 "<li>Protocol: %s</li>"
			 "</ul>", client_ip_address, ntohs(client_addr->sin_port), request.method, request.uri, request.protocol);

	send(client_sock, response_header, strlen(response_header), 0);
	send(client_sock, response_content, strlen(response_content), 0); 

	//parsePathAndParameters(request.uri);

	releaseHeaderFields(&fields);

	close(client_sock);
}