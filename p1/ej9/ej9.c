#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

volatile int contador=0; 

//Funcion que trata la señal SIGUSR1

void tratarSenal(int sig){
    if(sig==SIGUSR1){
        contador++;
        printf("\nHijo de pid %d ha recibido la señal SIGUSR1 del padre %d, contador=%d\n", getpid(), getppid(), contador);

        if(contador==5){ //Si ha recibido 5 señales, termina
            exit(EXIT_SUCCESS);
        }

        if(signal(SIGUSR1, tratarSenal)==SIG_ERR){ //Si hay un error al reasignar la señal sale del programa
            perror("\nError en la re-asignacion de la señal\n");
            exit(EXIT_FAILURE);
        }
    }
}

int main(){

    pid_t pid;
    pid = fork();
    int i;

    printf("\nPadre %d, crea al hijo %d\n", getpid(), getppid());

    if(pid<0){
        printf("\nError al crear el hijo\n"); 
        exit(EXIT_FAILURE);
    } else if(pid == 0){ //Proceso hijo
        
        if(signal(SIGUSR1, tratarSenal)==SIG_ERR){ //Si hay un error al asignar la señal sale del programa
            perror("\nError en la asignacion de la señal\n");
            exit(EXIT_FAILURE);
        }

        printf("\nHijo %d esperando señales del padre %d\n", getpid(), getppid());
        while(1){
                //Bucle infinito esperando señales
        }
    } else {

        printf("\nPadre %d enviando señales a su hijo %d\n", getpid(), pid); //Proceso padre
        for(i=0; i<=5; i++){
            
            printf("\nPadre %d enviando señal SIGUSR1 a su hijo %d\n", getpid(), pid);

            if(kill(pid, SIGUSR1)==-1){
                perror("\nError al enviar la señal\n");
                exit(EXIT_FAILURE);
             }
            sleep(1);
        }

        printf("\nPadre %d esperando a que su hijo %d termine\n", getpid(), pid);

        int status;

        //Esperamos al hijo

        if(wait(&status)==-1){
            perror("\nError en el wait\n");
            exit(EXIT_FAILURE);
        }

        printf("\nPadre %d: hijo %d ha terminado\n", getpid(), pid);
        exit(EXIT_SUCCESS);

    }

    exit(EXIT_SUCCESS);

}