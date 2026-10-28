#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]){

    if(argc != 2){
        printf("Uso: %s <Numero de hijos>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int numeroHijos = atoi(argv[1]);
    pid_t pidC;

    for(int i = 0; i < numeroHijos; i++){

        pidC = fork();

        if(pidC == -1){

            perror("fork error\n");
            printf("fork value: %d\n", errno);
            exit(EXIT_FAILURE);

        } else if(pidC == 0){

            printf("[HIJO%d] Mi PID es: %d, mi padre tiene PID %d\n", i+1, getpid(), getppid());
            sleep(10);
            exit(EXIT_SUCCESS);

        }
    }

    int status;
    pid_t childP;

    for(int i = 0; i < numeroHijos; i++){

        childP = wait(&status);
        if(WIFEXITED(status)){

            printf("[PADRE] El hijo con pid %d ha terminado con status %d\n", childP, WEXITSTATUS(status));
    
        } else {

            printf("[PADRE] El hijo %d ha terminado anormalmente", i + 1);
        }
    }

    printf("\n");

    exit(EXIT_SUCCESS); 

}