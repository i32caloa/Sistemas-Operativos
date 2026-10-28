#include <sys/types.h>
#include <sys/wait.h>
#include <wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]){

    if(argc != 2){

        printf("Uso: %s <Numero de Hijos>\n", argv[0]);
        exit(EXIT_FAILURE);

    }

    int numeroHijos = atoi(argv[1]);
    pid_t pidC;

    for(int i = 0; i < numeroHijos; i++){

        pidC = fork();

        switch(pidC){

            case -1:

                printf("Error al usar fork\n");
                printf("fork value: %d\n", errno);
                exit(EXIT_FAILURE);

            case 0:

                printf("[HIJO%d] Mi PID es %d, mi padre tiene PID %d\n", i + 1, getpid(), getppid());
                sleep(10 * (i + 1));
                exit(EXIT_SUCCESS);

            default:

                printf("[PADRE] Hijo %d creado correctamente con PID %d\n", i + 1, pidC);
                break;

        }       
    }

    int status;
    pid_t childP;

    for(int i = 0; i < numeroHijos; i++){

        childP = wait(&status);

        if(WIFEXITED(status)){

            printf("[PADRE] El hijo %d con PID %d ha terminado con status %d\n", i + 1, childP, WEXITSTATUS(status));

        } else {

            printf("[PADRE] Hijo %d con PID %d ha terminado de manera anormal\n", i + 1, childP);
            
        }

    }

    printf("\n");
    exit(EXIT_SUCCESS);

}