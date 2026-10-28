#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

int main(int argc, char *argv[]){

    if(argc < 3){

        printf("Uso: %s <calculadora> <editor> <ficheros>\n", argv[0]);
        exit(EXIT_FAILURE);

    }

    pid_t calc, editor;

    calc = fork();
    
    if(calc == -1){

        printf("Error en fork calculadora, codigo errno %d\n", errno);
        exit(EXIT_FAILURE);

    } else if(calc == 0){

        printf("[HIJOCalc] Iniciando calculadora: %s\n", argv[1]);
        execlp(argv[1], argv[1], NULL);

        perror("Error al ejecutar la calculadora\n");
        exit(EXIT_FAILURE);

    }

    editor = fork();

    if(editor == -1){

        printf("Erro en fork editor, codigo errno %d\n", errno);
        exit(EXIT_FAILURE);

    } else if(editor == 0){

        printf("[HIJOEDITOR] Iniciando editor: %s", argv[2]);
        execvp(argv[2], &argv[2]);

        printf("Error al ejecutar el editor\n");
        exit(EXIT_FAILURE);

    }

    int status;
    pid_t childPid;

    while((childPid = wait(&status)) > 0){

        if(WIFEXITED(status)){

            printf("[PADRE] El hijo con PID %d ha terminado con status %d\n", childPid, WEXITSTATUS(status));

        } else {

            printf("[PADRE] Hijo con PID %d ha terminado de manera anormal\n", childPid);

        }
    }

    exit(EXIT_SUCCESS);
}