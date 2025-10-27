#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[]){

    if(argc!=3){
        printf("\nUso: %s <nombre_fichero> <num_hijos>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    //1.Declaramos variables 

    int num_hijos = atoi(argv[2]);

    if(num_hijos<=0){
        printf("\nError, el numero de hijos no puede ser 0\n");
        exit(EXIT_FAILURE);
    }

    char fichero[100];
    strcpy(fichero, argv[1]);

    //2.Abrir el fichero

    FILE *f = fopen(fichero, "w");
    if(f==NULL){
        perror("\nError al abrir el fichero\n");
        exit(EXIT_FAILURE);
    }

    printf("\nPadre %d ha abierto el fichero %s y ha creado hijos.... %d\n", getpid(), fichero, num_hijos);

    pid_t pid;

    //3.Bucle para los hijos

    for(int i=0; i<num_hijos; i++){
        pid = fork();
        if(pid<0){
            printf("\nError, el pid es menor a 0\n");
            exit(EXIT_FAILURE);
        } else if(pid==0){

            for (int j = 0; j < 3; j++){
            fprintf(f, "Hijo %d (PID %d) - Escritura %d\n", i, getpid(), j+1);
            fflush(f); // Asegura la escritura inmediata
            }
            exit(EXIT_SUCCESS);
        }
    }

    //4.Se espera al hijo

    for(int i=0; i<num_hijos; i++){
        wait(NULL);
    }

    //5.Se cierra el fichero

    fclose(f);

    //6.Mostramos el contenido del fichero en pantalla

    printf("\n---Contenido del fichero %s---\n", fichero);
    execlp("cat", "cat", fichero, (char*)NULL);
    perror("\nERROR al ejecutar cat");

    exit(EXIT_FAILURE);
}