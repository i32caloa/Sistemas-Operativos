#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>

int main(int argc, char *argv[]){

    if(argc!=2){
        printf("\nUso: %s <ID>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t pid = atoi(argv[1]);

    if(kill(pid,0)==-1){
        perror("\nError al crear el proceso\n");
        exit(EXIT_FAILURE);
    }

    printf("\nEnviando SIGUSR1 a %d\n", pid);
    if(kill(pid, SIGUSR1)==-1){
        perror("\nError al enviar la señal\n");
        exit(EXIT_FAILURE);
    }

    sleep(1);

    printf("\nEnviando SIGKILL a %d\n", pid);
    if(kill(pid, SIGKILL)==-1){
        perror("\nError al enviar la SIGKILL\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);

}