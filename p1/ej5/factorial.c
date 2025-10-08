#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){

    if(argc!=3){
        printf("\nUso: %s <num1> <num2>", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t pid1, pid2;
    pid1=fork();

    if(pid1==0){
        execlp("./ej5", "./ej5", argv[1], NULL);
        printf("\nError de execlp\n");
        exit(EXIT_FAILURE);
    }

    pid2=fork();
    if(pid2==0){
        execlp("./ej5", "./ej5", argv[2], NULL);
        printf("\nError de execlp\n");
        exit(EXIT_FAILURE);
    }

    wait(NULL);
    wait(NULL);

    exit(EXIT_FAILURE);
}