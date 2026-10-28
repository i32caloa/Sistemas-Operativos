#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

void *suma(void *argc){

    float *suma = (float *)malloc(sizeof(float));

    float num1 = ((float)rand() / RAND_MAX) * 100.0;
    float num2 = ((float)rand() / RAND_MAX) * 100.0;

    *suma = num1 + num2;

    printf("Hebra ID: %lu\n->Número 1: %.2f\n->Número 2: %.2f\n->Suma: %.2f\n", (unsigned long)pthread_self(),num1, num2, *suma);

    pthread_exit((void*) suma);

}

int main(int argc, char *argv[]){

    if(argc != 2){
        printf("Uso: %s <numero_hebras>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    float *sumaH;
    float resultado = 0.0;
    int NUMERO_HEBRAS = atoi(argv[1]);

    if(NUMERO_HEBRAS <= 0){
        printf("El numero de hebras debe de ser >= 0\n");
    }

    pthread_t thr[NUMERO_HEBRAS];

    for(int i = 0; i < NUMERO_HEBRAS; i++){
        if(pthread_create(&thr[i], NULL, suma, NULL) != 0){
            printf("Error al crear el hilo %d, con errno %d\n", i + 1, errno);
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i < NUMERO_HEBRAS; i++){
        if(pthread_join(thr[i], (void **)&sumaH) != 0){
            printf("Error al esperar la hebra %d con errno %d", i + 1, errno);
            exit(EXIT_FAILURE);
        }

        if(sumaH != NULL){
            resultado += *sumaH;
            free(sumaH);
        }
    }

    printf("Suma total calculada: %.2f\n", resultado);


    exit(EXIT_SUCCESS);
}