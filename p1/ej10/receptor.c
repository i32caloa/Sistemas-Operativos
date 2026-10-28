#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void manejador(int sig){
    printf("[RECEPTOR] Señal SIGUSR1 capturada, PID %d\n", getpid());
}

int main(){

    if(signal(SIGUSR1, manejador) == SIG_ERR){
        perror("Error en la señal SIGUSR1\n");
        exit(EXIT_FAILURE);
    }

    printf("[RECEPTOR] Proceso a la espera con PID: %d\n", getpid());

    while(1){
        pause();
    }

    return 0;
}