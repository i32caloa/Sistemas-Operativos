#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int contador = 0;

int main(int argc, char *argv[]){

    if(argc != 2){
        printf("Uso: %s <numero_hijos>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int numero_hijos = atoi(argv[1]);
    pid_t childP;

    for(int i = 0; i < numero_hijos; i++){
        childP = fork();

        if(childP == -1){
            printf("Error en fork %d\n", errno);
            exit(EXIT_FAILURE);
        } else if(childP == 0){
            printf("[HIJO %d] Hijo con PID %d suma al contador\n", i + 1, getpid());
            contador++;

            printf("Contador: %d\n", contador);

            sleep(10);
            exit(EXIT_SUCCESS);
        }
    }

    int status;
    pid_t pidC;

    while(pidC == wait(&status)){
        if(WIFEXITED(status)){
            printf("[PADRE] Hijo con PID %d ha terminado con status %d\n", pidC, WEXITSTATUS(status));
        } else {
            printf("[PADRE] Hijo con PID %d ha terminado de manera anormal\n", pidC);
        }
    }

    printf("Contador: %d\n", contador);

    exit(EXIT_SUCCESS);
}