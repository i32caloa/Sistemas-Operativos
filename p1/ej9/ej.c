#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

static volatile int contador = 0;

void sign(int sig){
    contador++;
    printf("[HIJO] Recibida la señal SIGUSR1 del padre (%d/5)\n", contador);
}

int main(){
    pid_t pidC;

    pidC = fork();

    if(pidC == -1){
        perror("Errror en fork\n");
        exit(EXIT_FAILURE);
    } else if(pidC == 0){
        if(signal(SIGUSR1, sign) == SIG_ERR){
            perror("Error al asocial SIGUSR1\n");
            exit(EXIT_FAILURE);
        }

        while(contador < 5){
            pause();
        }

        printf("[HIJO] Recibidas las 5 señales\n");
        exit(EXIT_SUCCESS);
    }

    for(int i = 0; i < 5; i++){
        sleep(1);
        printf("[PADRE] Enviado señal SIGUSR1 al hijo (%d/5)\n", i + 1);

        if(kill(pidC, SIGUSR1) == -1){
            perror("ERRor al enviar la señal con kill\n");
            exit(EXIT_FAILURE);
        }
    }

    int status;

    wait(&status);
    if(WIFEXITED(status)){
        printf("[PADRE] Hijo finalizado con status %d\n", status);
    }

    exit(EXIT_SUCCESS);

}