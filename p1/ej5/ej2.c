#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char *argv[]){

    if(argc != 3){

        printf("Uso: %s <numero1> <numero2>\n", argv[0]);
        exit(EXIT_FAILURE);

    }

    pid_t numero1, numero2;

    numero1 = fork();

    if(numero1 == -1){

        printf("Error en fork numero1 con errno %d\n", errno);
        exit(EXIT_FAILURE);

    } else if(numero1 == 0){

        printf("[HIJO1] Hijo con PID %d y padre %d calcula el factorial de %s\n", getpid(), getppid(), argv[1]);
        execlp("./factorial.exe", "./factorial.exe", argv[1], NULL);

        printf("[HIJO1] Error execlp\n");
        exit(EXIT_FAILURE);

    }

    numero2 = fork();

    if(numero2 == -1){

        printf("Error en fork numero2 con errno %d\n", errno);
        exit(EXIT_FAILURE);


    } else if(numero2 == 0){

        printf("[HIJO2] Hijo con PID %d y padre %d calcula el factorial de %s\n", getpid(), getppid(), argv[2]);
        execlp("./factorial.exe", "./factorial.exe", argv[2], NULL);

        printf("[HIJO2] Error execlp\n");
        exit(EXIT_FAILURE);
        
    }

    int status;
    pid_t childP;
    
    while((childP = wait(&status)) > 0){

        if(WIFEXITED(status)){

            printf("[PADRE] Hijo con PID %d ha terminado con status %d\n", childP, WEXITSTATUS(status));

        } else {

            printf("[PADRE] Hijo con PID %d ha terminado de manera anormal\n", childP);
        }
    }

    exit(EXIT_FAILURE);
}