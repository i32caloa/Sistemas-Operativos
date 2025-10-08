#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    
    if(argc<3){
        printf("\nUso: %s <calculadora> <editor> archivo1 archivo2......", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t pid;
    pid=fork();

	if(pid==0){
		execlp(argv[1], argv[1], NULL); // Ejecutar la calculadora
		printf("execlp ha dado error.");
		exit(EXIT_FAILURE);
    }

    pid = fork();

	if(pid==0){
		execvp(argv[2], argv+2); // Ejecutar el editor con los archivos [execvp para muchos archivos] (Empieza a partir del tercer valor porque los dos primeros son la calculadora y el editor de texto)
		printf("execvp ha dado error.");
		exit(EXIT_FAILURE);
	}

    wait(NULL);
    wait(NULL);

    exit(EXIT_SUCCESS);
}