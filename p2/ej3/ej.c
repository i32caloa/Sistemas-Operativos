#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>

struct DatosHebra{

    int *vector;
    int inicio;
    int fin;
    int id;
};

void *sumar_subvector(void *arg){
    struct DatosHebra *datos = (struct DatosHebra*)arg;
    int suma_parcial = 0;

    int *resultado = (int*)malloc(sizeof(int));
    if(resultado == NULL){
        perror("Error al reservar la memoria para los resultados de la hebra\n");
        exit(EXIT_FAILURE);
    }

    for(int i = datos->inicio; i < datos->fin; i++){
        suma_parcial += datos->vector[i];
    }

    *resultado = suma_parcial;

    return (void*) resultado;
    
}

int main(int argc, char *argv[]){

    if(argc != 2){
        printf("Uso: %s <2 o 5>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int numero_hebras = atoi(argv[1]);
    int vector[10];
    int elementos_hebra = 0;
    int suma_total = 0;

    int *resultado_parcial = NULL;

    srand(time(NULL));

    if(numero_hebras != 2 && numero_hebras != 5){
        printf("El numero de hebras debe de ser 2 o 5\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < 10; i++){
        vector[i] = (rand() % 9) +1;
        printf("%d ", vector[i]);
    }

    printf("\n");

    elementos_hebra = 10 / numero_hebras;

    pthread_t *hilos = (pthread_t*)malloc(numero_hebras * sizeof(pthread_t));
    struct DatosHebra *datos = (struct DatosHebra*)malloc(numero_hebras * sizeof(struct DatosHebra));

    if(hilos == NULL || datos == NULL){
        perror("Error al reservar la memoria\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < numero_hebras; i++){
        datos[i].vector = vector;
        datos[i].inicio = i * elementos_hebra;
        datos[i].fin = (i + 1) * elementos_hebra;
        datos[i].id = i;

        if(pthread_create(&hilos[i], NULL, sumar_subvector, (void*)&datos[i]) != 0){
            printf("Error al crear la hebra %d\n", i + 1);
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i < numero_hebras; i++){
        if(pthread_join(hilos[i], (void**)&resultado_parcial) != 0){
            printf("Error al recibir la hebra %d\n", i + 1);
            exit(EXIT_FAILURE);
        }
        if(resultado_parcial != NULL){
            printf("Hebra %d finalizada\n > Suma parcial: %d\n", i, *resultado_parcial);
            suma_total += *resultado_parcial;
            free(resultado_parcial);
        }
    }

    printf("\n >> Suma total: %d\n", suma_total);

    free(hilos);
    free(datos);

    exit(EXIT_SUCCESS);
}