#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void *contar_lineas_fichero(void *arg){

    char *nombre_fichero = (char*)arg;
    int caracter = 0;
    long nlineas = 0;

    long *resultado = (long*)malloc(sizeof(long));
    if(resultado == NULL){
        perror("Error al reservar la memoria\n");
        exit(EXIT_FAILURE);
    }

    FILE *fichero = fopen(nombre_fichero, "r");
    if(fichero == NULL){
        perror("Error al abrir el fichero\n");
        exit(EXIT_FAILURE);        
    }

    while((caracter = fgetc(fichero)) != EOF){
        if(caracter == '\n'){
            nlineas++;
        }
    }

    if(fclose(fichero) != 0){
        perror("Error al cerrar el fichero\n");
        exit(EXIT_FAILURE);
    }

    *resultado = nlineas;
    
    pthread_exit((void*)resultado);

}

int main(int argc, char *argv[]){

    if(argc < 2){
        fprintf(stderr, "[PADRE] Uso: %s <nombre_fichero1>.....<nombre_ficheroN>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int numero_ficheros = argc - 1;
    long lineas_totales = 0;
    long *resultado_hilos = NULL;

    pthread_t *hilos = (pthread_t*)malloc(numero_ficheros * sizeof(pthread_t));
    if(hilos == NULL){
        perror("[PADRE] Error al reservar memoria para los id de los hijos");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < numero_ficheros; i++){
        if(pthread_create(&hilos[i], NULL, contar_lineas_fichero, (void*)argv[i + 1]) != 0){
            fprintf(stderr, "[PADRE] Error al crear el hilo %d\n", i + 1);
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i < numero_ficheros; i++){
        if(pthread_join(hilos[i], (void**)&resultado_hilos) != 0){
            fprintf(stderr, "[PADRE] Error en la espera del hilo %d\n", i + 1);
            exit(EXIT_FAILURE);
        }

        if(resultado_hilos != NULL){
            printf("Fichero '%s'\n > %ld lineas\n", argv[i + 1], *resultado_hilos);
            lineas_totales += *resultado_hilos;
            free(resultado_hilos);
        }
    }

    printf("\nNumero de lineas sumando los %d ficheros: %ld\n", numero_ficheros, lineas_totales);

    free(hilos);

    exit(EXIT_SUCCESS);
}