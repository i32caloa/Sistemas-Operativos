#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){

    if(argc!=2){
        printf("\nUso: %s <num_hijos>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int num_hijos = atoi(argv[1]);

    pid_t pid;

    for(int i=0; i<num_hijos; i++){

        pid = fork();

        if(pid<0){
            perror("\nERROR, pid menor a 0\n");
            exit(EXIT_FAILURE);
        } else if(pid==0){
            printf("\nSoy el hijo %d de padre %d, esperando %d segundos ", getpid(), getppid(), 10*i);
            sleep(10*i);
            exit(EXIT_SUCCESS);
        }
    }

    int status;

    for(int i=0; i<num_hijos; i++){
        wait(&status);
        if(WIFEXITED(status)){
            printf("\nEl hijo %d ha terminado con id %d", i+1, WEXITSTATUS(status));
        } else {
            printf("\nEl hijo %d ha terminado de forma anormal", i+1);
        }
    }

    printf("\n");

    exit(EXIT_SUCCESS);
}