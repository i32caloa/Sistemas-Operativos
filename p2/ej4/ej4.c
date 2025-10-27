/*
4.4 Ejercicio4
Implemente un programa que cree dos hebras y cada una incremente 1.000.000 veces en un
bucle una variable global (recuerde que la variable global, al estar en el mismo espacio de memoria
para las dos hebras, es compartida, y que su uso es “peligroso”). Imprima al final del programa
principal el valor de la variable (en cada ejecución posiblemente obtenga un valor diferente a
2.000.000 – problema de concurrencia –). Intente razonar el resultado, el cual le servirá como
concepto introductorio de la siguiente práctica de la asignatura.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_INCREMENTS 1000000
#define NUM_THREADS 2

long long global_counter = 0; // Variable global long long para evitar overflow

// Función que incrementa el contador global

void *incrementarContador(void *argc){
    for(long long i = 0; i < NUM_INCREMENTS; i++){
        global_counter++;
    }
    return NULL;
}

int main(void){

    pthread_t threads[NUM_THREADS];

    // Crear las hebras

    for(int i = 0; i < NUM_THREADS; i++){
        if(pthread_create(&threads[i], NULL, incrementarContador, NULL) != 0){
            perror("Error al crear la hebra");
            exit(EXIT_FAILURE);
        }
    }

    // Esperar a que las hebras terminen

    for(int i=0; i<NUM_THREADS; i++){
        if(pthread_join(threads[i], NULL) !=0){
            perror("Error al esperar la hebra");
            exit(EXIT_FAILURE);
        }
    }

    printf("Valor final del contador global: %lld\n", global_counter);

    return 0;
}