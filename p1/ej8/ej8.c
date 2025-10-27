#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

static int count = 0;

//Funcion que al recibir la señal SIGALRM se ejecuta 

void controlador(int sig){ 
    if(count == 0){
        alarm(3); //Segunda alarma a los 3 segundos
        printf("\nRING\n");
    }

    if(count == 4){
        kill(getpid(), SIGTERM); //Se termina el proceso
    }

    if(count != 0){
        alarm(1); //Alarmas cada 1 segundo
        printf("\nRING\n");
    }
    count ++;
}

int main(){

    alarm(5); //Primera alarma a los 5 segundos
    signal(SIGALRM, controlador); //Asociamos la señal SIGALRM a la función controlador
    while(1){

    }

    return 0;
}

