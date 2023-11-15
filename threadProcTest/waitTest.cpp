#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
    int pid;
    pid = fork();
    if (pid < 0){
        printf("Error ");
        exit(-1);
    }
    else if (pid == 0){
        printf("C=%d\n", getpid());
        exit(0);
    }
    else { 
        wait(NULL);
        printf("P=%d\n", getpid());
        exit(0);
    }
}