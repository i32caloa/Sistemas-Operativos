#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    if(argc!=2){
        printf("\nUso: %s <num_hijos>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int global=0;
    int num_hijos = atoi(argv[1]);

    pid_t pid;

    for(int i=0; i<num_hijos; i++){

        pid = fork();

        if(pid<0){
            perror("\nError, el pid es menor o igual a 0");
            exit(EXIT_FAILURE);  
        } else if (pid==0){
            printf("\nSoy el hijo %d de padre %d", getpid(), getppid());
            global++;
            exit(EXIT_SUCCESS);
        }
    }

    int status;

    for(int i=0; i<num_hijos; i++){
        wait(&status);
        if(WIFEXITED(status)){
            printf("\nEl hijo %d ha terminado con id %d", i+1, WEXITSTATUS(status));
        } else {
            printf("\nEl hijo %d termino anormalmente", i+1);
        }
        printf("\nValor de la variable global en el padre: %d", global);
    }
    
    printf("\n");

    exit(EXIT_SUCCESS);
}