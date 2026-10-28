#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

int main(int argc, char *argv[]){

    if(argc != 2){
        printf("Uso: %s <PID_RECPETOR>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t destino = atoi(argv[1]);

    printf("[EMISOR] Enviando SIGUSR1 al proceso %d\n", destino);
    if(kill(destino, SIGUSR1) == -1){
        printf("Error al enviar SIGUSR1\n");
        exit(EXIT_FAILURE);
    }

    sleep(1);

    printf("[EMISOR] Enviando SIGKILL al proceso%d\n", destino);
    if(kill(destino, SIGKILL) == -1){
        perror("Error al mandar la señal SIGKILL\n");
        exit(EXIT_FAILURE);
    }

    if(kill(destino, 0) == -1 && errno == ESRCH){
        printf("[EMISOR] Confirmado: El proceso con PID %d ya NO existe en el sistema.\n", destino);
    } else {
        printf("[EMISOR] El proceso con PID %d aún existe en el sistema.\n", destino);
    }

    exit(EXIT_SUCCESS);

}