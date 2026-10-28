#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]){

    if(argc != 3){

        printf("Uso: %s <fichero> <numero_hijos>\n", argv[0]);
        exit(EXIT_FAILURE);

    }

    int numero_hijos = atoi(argv[2]);
    pid_t pidC;
    char nombre_fichero[256];
    strcpy(nombre_fichero, argv[1]);

    FILE *f = fopen(nombre_fichero, "a");

    if(f == NULL){

        perror("[ERROR] Error al abrir el fichero txt.txt\n");
        exit(EXIT_FAILURE);

    }

    for(int i = 0; i < numero_hijos; i++){

        pidC = fork();

        if(pidC == -1){

            printf("[HIJO %d] Error en fork con errno %d\n", i + 1, errno);
            exit(EXIT_FAILURE);

        } else if(pidC == 0){

            for(int j = 1; j < numero_hijos; j++){

                fprintf(f, "Hijo %d ha escrito en la linea %d\n", i + 1, j);
                fflush(f);

            }

            exit(EXIT_SUCCESS);

        }
    }

    int status; 
    pid_t childP;



    while((childP = wait(&status)) > 0){

        if(WIFEXITED(status)){

            printf("[PADRE] El hijocon pid %d ha terminado con status %d\n", childP, WEXITSTATUS(status));

        } else {

            printf("[PADRE] Hijo con PID %d terminado de manera anormal\n", childP);

        }

    }

    fclose(f);
    printf("[PADRE] El proceso de escritura ha terminado\n");

    execlp("cat", "cat", nombre_fichero, NULL);
    perror("Error en el cat\n");

    exit(EXIT_SUCCESS);

}