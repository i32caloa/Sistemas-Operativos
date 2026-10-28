#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int variable_global = 0;

void *incrementar_variable(void *arg){
    for(int i = 0; i < 1000000; i++){
        variable_global++;
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    
    int numero_hebras = 2;

    pthread_t *hilos = (pthread_t*)malloc(numero_hebras * sizeof(pthread_t));

    if(hilos == NULL){
        perror("Error al reservar la memoria\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < numero_hebras; i++){
        if(pthread_create(&hilos[i], NULL, incrementar_variable, NULL) != 0){
            printf("Error al crear la hebra %d\n", i + 1);
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i < numero_hebras; i++){
        if(pthread_join(hilos[i], NULL) != 0){
            printf("Error al recibir la hebra %d\n", i + 1);
            exit(EXIT_FAILURE);
        }
    }

    printf("Valor de la variable global %d\n", variable_global);
    free(hilos);

    exit(EXIT_SUCCESS);
}