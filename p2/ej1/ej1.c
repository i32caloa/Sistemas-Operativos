#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

void *sumar_numeros(void *argc){

    float *suma = (float*)malloc(sizeof(float));

    float num1 = ((float)rand() / RAND_MAX) * 100.0;
    float num2 = ((float)rand() / RAND_MAX) * 100.0;
    
    *suma = num1 + num2;

    printf("[HEBRA %ld] \n > Numero 1 = %.2f \n > Numero 2 = %.2f \n > Suma = %.2f\n", (unsigned long)pthread_self(), num1, num2, *suma);

    pthread_exit((void*)suma);

}

int main(int argc, char *argv[]){

    if(argc != 2){
        printf("Uso: %s <numero_hebras>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int numero_hebras = atoi(argv[1]);
    float resultado = 0.0;
    float *suma_hebras;

    srand(time(NULL));

    if(numero_hebras <= 0){
        printf("[PADRE] Se necesita un numero positivo de hebras\n");
        exit(EXIT_FAILURE);
    }

    pthread_t thr[numero_hebras];

    for(int i = 0; i < numero_hebras; i++){
        if(pthread_create(&thr[i], NULL, sumar_numeros, NULL) != 0){
            printf("\n[PADRE] Error al crear la hebra %d, con errno = %d\n", i + 1, errno);
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i < numero_hebras; i++){
        if(pthread_join(thr[i], (void**)&suma_hebras) != 0){
            printf("[PADRE] Error al esperar la hebra %d, con errno = %d\n", i + 1, errno);
        }

        if(suma_hebras != NULL){
            resultado += *suma_hebras;
            free(suma_hebras);
        }
    }

    

    printf("[PADRE] Suma total de las %d hebras = %.2f\n", numero_hebras, resultado);

    exit(EXIT_SUCCESS);

}