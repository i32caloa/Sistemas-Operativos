#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]){

    if(argc!=2){
        printf("\nUso: %s <num>", argv[0]);
        exit(EXIT_FAILURE);
    }

    int num = atoi(argv[1]);
    int resultado=1;

    for(int i=1; i<=num; i++){
        resultado*=i;
        sleep(1);
    }

    printf("\nEl factorial es: %d", resultado);

    exit(EXIT_SUCCESS);
}