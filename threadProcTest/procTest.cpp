#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
    int pid;
    pid = fork();
    if (pid < 0){
        printf("Error ");
        exit(-1);
    }
    else if (pid == 0){
        printf("Child");
        exit(0);
    }
    else {
        printf("Parent");
        exit(0);
    }
}