#include <iostream>
#include <thread>
#include <pthread.h>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <csignal>
using namespace std;

#define PACKET_SIZE 1024
//#define serverPort 7000

struct ClientInfo { // Ŭ���̾�Ʈ ���� �ʵ�
	int socket;
	sockaddr_in clientAddress;
};

vector<pthread_t> clientThreads;    // ��������� ������ vector ����
vector<ClientInfo*> clientPool;     // Ŭ���̾�Ʈ ���� ����ü�� ������ vector ����

int server_socket;                  // ���� ����
void* handle_client(void* data);    // Ŭ���̾�Ʈ ���� thread �Լ�
void* client_accept(void* data);    // Ŭ���̾�Ʈ ���� thread �Լ�

void signalHandler(int signum) {
    std::cout << "���α׷��� ���ͷ�Ʈ(SIGINT)�� ���� ����Ǿ����ϴ�." << std::endl;
    // �߰��� ������ �۾��� �ִٸ� ���⿡�� ó�� ����
    exit(signum); // ����
}

int main(int argc, char* argv[]){

    if (argc != 2) {
        cerr << "����: " << argv[0] << " <���� ��Ʈ ��ȣ>" << endl;
        return 1;
    }

    signal(SIGINT, signalHandler); // SIGINT ���� signal �ڵ鷯 ���

    int optvalue = 1; // sockopt optvalue
    struct sockaddr_in serverAddr;

    // server socket ����
    server_socket = socket(AF_INET, SOCK_STREAM, 0); 
    if (server_socket == -1) {
        cerr << "���� ���� ���� ����" << endl;
        //perror("socket");
        
        return 1;
    }
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &optvalue, sizeof(optvalue));

    memset(&serverAddr, 0, sizeof(serverAddr)); // sockaddr_in �ʱ�ȭ

    int serverPort = atoi(argv[1]);
    /*
    while (true){
        cout << "��Ʈ ��ȣ�� �Է��ϼ���: ";
        cin >> serverPort;
        if (std::cin.fail()) {
            cout << "�Է��� �ùٸ� ������ �ƴմϴ�. �ٽ� �Է��� �ּ���." << endl;

            // ���� �÷��׸� �ʱ�ȭ�Ͽ� �Է� ��Ʈ���� ���� ���·� ��ȯ
            cin.clear();
            
            // �߸��� �Է� ����
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            if(serverPort <= 65000 && 1024 <= serverPort) {
                cout << "�Է��� ��Ʈ ��ȣ: " << serverPort << endl;
                break;
            } else {
                cout << "�������� ��Ʈ ������ �Է��� �ּ���. (1024 ~ 65000)" << endl;
            }
        }
    }
    */

    if(serverPort <= 65000 && 1024 <= serverPort) {
        cout << "�Է��� ��Ʈ ��ȣ: " << serverPort << endl;
    } else {
        cout << "�������� ��Ʈ ������ �Է��� �ּ���. (1024 ~ 65000)" << endl;
        return -1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(serverPort);

    // ���� ������ �ּҿ� ���ε�
    int bindResult = ::bind(server_socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (bindResult < 0) {
        cerr << "���ε� ����" << endl;
        //perror("bind");

        close(server_socket);
        return 1;
    }

    listen(server_socket, 5); // 5�� ��α� ũ�� = ���ÿ� ó�� ������ ���� ��û�� �ִ� ��
    cout << "������ "<< serverPort << " ��Ʈ���� ��� ��..." << endl;

    pthread_t thread_listen; // Ŭ���̾�Ʈ ���� ��û�� ������ ������ ����
    if (pthread_create(&thread_listen, NULL, client_accept, NULL) != 0) {
        cerr << "������ ���� ����" << endl;
        return 1;
    }

    char msg[PACKET_SIZE] = {0};

    while (1) {
        // �޼��� ���� �ʱ�ȭ�ϰ� �Է¹ޱ�
        memset(msg, 0, PACKET_SIZE);
        cin.getline(msg, PACKET_SIZE);
        if ((string)msg == "list") { // �Է��� ���� "list"�� ����� Client ��� ���
            cout << "����� Client IP Address ���" << endl;
			for (size_t i = 0; i < clientPool.size(); ++i) {
				cout << inet_ntoa(clientPool[i]->clientAddress.sin_addr) << ":" << ntohs(clientPool[i]->clientAddress.sin_port) << endl;
			}
        } else if ((string)msg == "exit") {
            cout << "Server�� �����մϴ�." << endl;
            pthread_detach(thread_listen);
            break;
        } 
        else { // �Է��� ���� "list", "exit"�� �ƴϸ� ����� Client�鿡�� �޼��� ����
            for (size_t i = 0; i < clientPool.size(); ++i) {
				send(clientPool[i]->socket, msg, strlen(msg), 0);
			}
        }
    }

    pthread_join(thread_listen, NULL);
    /* �޸� �Ҵ� ���� */
    for (size_t i = 0; i < clientPool.size(); ++i){
        cout << "clientPool �޸� �Ҵ� ����: " << clientPool[i]->socket << endl;
        delete clientPool[i];
    }
    for(size_t i = 0; i < clientThreads.size(); ++i){
        cout << "clientThreads �޸� �Ҵ� ����: " << clientThreads[i] << endl;
        pthread_detach(clientThreads[i]);
    }
    /* �޸� �Ҵ� ���� */

    // ���� ���� �ݰ� ���α׷� ����
    close(server_socket);
    return 0;
}

void* client_accept(void* data){    // Ŭ���̾�Ʈ ���� thread �Լ�
    while(1) {
        int client_socket;
        struct sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);

        client_socket = accept(server_socket, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (client_socket == -1) {
            // Ŭ���̾�Ʈ ���� ���� �� ������ �ݰ� ���� while ȸ���� �Ѿ
            std::cerr << "Ŭ���̾�Ʈ ���� ���� ����" << std::endl;
            //perror("client");
            close(client_socket);
            continue;
        }

        cout << "Ŭ���̾�Ʈ�� ������ �Ϸ�Ǿ����ϴ�" << endl;
        cout << "Client IP: " << inet_ntoa(clientAddr.sin_addr) << endl;
		cout << "Port: " << ntohs(clientAddr.sin_port) << endl;
        
        // Ŭ���̾�Ʈ�� �����͸� ���� ����ü�� �����ϰ�
        // ����� Ŭ���̾�Ʈ�� ����ü ������ �����ϱ� ���� vector�� ���
        ClientInfo* clientData = new ClientInfo;
		clientData->socket = client_socket;
		clientData->clientAddress = clientAddr;

        clientPool.push_back(clientData);

        // Ŭ���̾�Ʈ�� ó���� ������ ����
        pthread_t thread_client;
        pthread_create(&thread_client, NULL, handle_client, (void*)clientData);
        clientThreads.push_back(thread_client);
    }
    return NULL;
}

void* handle_client(void* data){
    // void* Ÿ�� parameter�� ����� �� �ֵ��� ClientInfo* Ÿ������ ����ȯ
    ClientInfo* clientData = static_cast<ClientInfo*>(data);
    int clientSocket = clientData->socket;
	sockaddr_in clientAddr = clientData->clientAddress;

    char buffer[1024];
	int recvSize;

    do {
        // buffer �޸� �ʱ�ȭ�ϰ� recv>0�� ��� �޼����� ���������� �����Ͽ� buffer�� ���� ����ϰ� send��
        memset(buffer, 0, PACKET_SIZE);
		recvSize = recv(clientSocket, buffer, sizeof(buffer), 0);
		if (recvSize > 0) {
			cout << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << "�κ��� ���� �޼���: [" << buffer << "]�� echo�մϴ�." << endl;
			send(clientSocket, buffer, recvSize, 0);
		}
	} while (recvSize > 0);

    for (size_t i = 0; i < clientPool.size(); ++i) {
		if (clientPool[i]->socket == clientSocket) {
			// Ŭ���̾�Ʈ ���� ����
			cout << "Ŭ���̾�Ʈ�� ������ ����Ǿ����ϴ�: " << inet_ntoa(clientPool[i]->clientAddress.sin_addr) << ":" << ntohs(clientPool[i]->clientAddress.sin_port) << endl;
			clientPool.erase(clientPool.begin() + i);
			break;
		}
	}
    delete clientData;
    close(clientSocket);
    //pthread_detach(pthread_self());
    return NULL;
}