#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

using namespace std;

#define PRO_IDFR "/home/projects/memoryTest"
#define SHM_SIZE 1024

typedef struct {
    char parent_context[256];
    char child_context[256];
    int parent_pid;
    int child_pid;
} testStruct;

int main() {
    key_t key = ftok(PRO_IDFR, 'ShmKey');
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);

    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    testStruct* shmaddr = (testStruct *)shmat(shmid, NULL, 0);

    if (shmaddr == (char *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // ���� �޸𸮿� ������ ����
    //sprintf(shmaddr, "Hello, Shared Memory!!!");

    // �ٸ� ���μ������� ���� �޸� �б�
    pid_t pid = fork();

    if (pid > 0){
        shmaddr->parent_pid = getpid();
        memcpy(shmaddr->parent_context, "Hello, Shared Memory, I'm Parent.", 256);
        
        //sprintf(shmaddr, "Hello, Shared Memory, I'm Parent.");
    }
    if (pid == 0){
        //sprintf(shmaddr, "Hello, Shared Memory, I'm Child.");
    }


    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    
    if (pid > 0) {
        // �θ� ���μ������� �б�
        printf("Parent Process: %s Size: %d, pid: %d\n", shmaddr, sizeof(shmaddr), getpid());
    }

    if (pid == 0) {
        // �ڽ� ���μ������� �б�
        printf("Child Process: %s Size: %d, pid: %d\n", shmaddr, sizeof(shmaddr), getpid());
        exit(EXIT_SUCCESS);
    }

    // ���� �޸� �и�
    if (shmdt(shmaddr) == -1) {
        cout << "���� �޸� �и� ����: " << pid << endl;
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    // ���� �޸� ����
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        cout << "���� �޸� �и� ���� ����: " << pid << endl;
        perror("shmctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}