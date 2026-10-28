#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[]){

    if(argc != 2){

        printf("Uso: %s <numero de hijos>", argv[0]);
        exit(EXIT_FAILURE);

    }

    pid_t pidC, chilP;
    int numeroHijos = atoi(argv[1]);

    for(int i = 0; i < numeroHijos; i++){

        pidC = fork();

        if(pidC == -1){

            perror("Error en el fork\n");
            printf("fork value: %d\n", errno);
            exit(EXIT_FAILURE);

        } else if(pidC > 0){

            int status;

            chilP = wait(&status);
            if(WIFEXITED(status)){

                printf("[PADRE] El hijo %d con PID %d, ha terminado con status %d\n", i+1, chilP, WEXITSTATUS(status));

            } else {

                printf("[PADRE] El hijo %d ha terminado de manera anormal\n", i+1);

            }

        } else if(pidC == 0){

            printf("[HIJO%d] Mi PID es: %d, mi padre tiene PID %d\n", i+1, getpid(), getppid());
            exit(EXIT_SUCCESS);
        }
    }
}