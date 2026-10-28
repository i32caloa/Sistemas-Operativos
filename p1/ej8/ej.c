#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

static int count = 0;

void controlador(int sig){

    if(count == 0){
        printf("RING alarma inicial\n");
        alarm(3);
    } else {
        printf("RING alarma %d\n", count);
        alarm(1);
    }

    if(count == 4){
        printf("Limite de 4 alarmas alcanzado\n");
        kill(getpid(), SIGTERM);
    }

    count++;

}

int main(){
    signal(SIGALRM, controlador);
    alarm(5);

    while(1){
        pause();
    }

    return 0;
}