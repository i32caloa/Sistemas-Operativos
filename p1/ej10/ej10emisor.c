#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void manejar_sigusr1(int sig) {
    printf("\nProceso %d ha recibido la señal SIGUSR1\n", getpid());
}

int main(){

    if(signal(SIGUSR1, manejar_sigusr1)==SIG_ERR){
        perror("\nError al capturar la señal SIGUSR1\n");
        exit(EXIT_FAILURE);
    }

    printf("\nProceso receptor con PID %d esperando señales...\n", getpid());

    while(1){

    }

    exit(EXIT_SUCCESS); 

}