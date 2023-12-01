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

    // 공유 메모리에 데이터 쓰기
    //sprintf(shmaddr, "Hello, Shared Memory!!!");

    // 다른 프로세스에서 공유 메모리 읽기
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
        // 부모 프로세스에서 읽기
        printf("Parent Process: %s Size: %d, pid: %d\n", shmaddr, sizeof(shmaddr), getpid());
    }

    if (pid == 0) {
        // 자식 프로세스에서 읽기
        printf("Child Process: %s Size: %d, pid: %d\n", shmaddr, sizeof(shmaddr), getpid());
        exit(EXIT_SUCCESS);
    }

    // 공유 메모리 분리
    if (shmdt(shmaddr) == -1) {
        cout << "공유 메모리 분리 실패: " << pid << endl;
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    // 공유 메모리 제거
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        cout << "공유 메모리 분리 제거 실패: " << pid << endl;
        perror("shmctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}