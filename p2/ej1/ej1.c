/*
4.1 Ejercicio1
Implemente un programa que cree un número N de hebras. Cada hebra creará 2 números
aleatorios flotantes (hacer con rand()) y guardará su suma en una
variable para ello, que será devuelta a la hebra principal o llamadora (la que invocó
pthread_create()).
La hebra principal ira recogiendo los valores devueltos por las N hebras y los ira sumando en
una variable no global cuyo resultado mostrará al final por pantalla. Para ver que los resultados
finales son los que usted espera, muestre los 2 números que va creando cada hebra y su suma, de
forma que pueda comparar esas sumas parciales con la suma final que realizará el main() o hebra
principal. Utilice macros definidas y comprobación de errores en sus programas (errno y
comprobación de valores devueltos en cada llamada, con sus posibles alternativas)
*/

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define NUM_THREADS 3

void *SumarNumeros(void *argc){

    float *resultado = malloc(sizeof(float));
    if(resultado==NULL){
        perror("Error al reservar memoria");
        pthread_exit(NULL);
    }

    /* generar dos números aleatorios en [0, RAND_SCALE) */
    float num1 = ((float)rand() / (float)RAND_MAX);
    float num2 = ((float)rand() / (float)RAND_MAX);
    *resultado = num1 + num2;

    printf("\nHebra %ld: num1 = %.4f, num2 = %.4f, suma = %.4f", pthread_self(), num1, num2, *resultado);

    return resultado;
}

int main(void){

    pthread_t thread[NUM_THREADS];
    float resultado = 0.0;

    //Creamos hebras

    for(int i=0; i<NUM_THREADS; i++){
        if(pthread_create(&thread[i], NULL, SumarNumeros, NULL) != 0){
            perror("Error al crear la hebra");
            exit(EXIT_FAILURE);
        }
    }

    //Recogemos resultados
    for(int i=0; i<NUM_THREADS; i++){
        float *suma;
        if(pthread_join(thread[i], (void **) &suma) != 0){
            perror("Error al esperar la hebra");
            exit(EXIT_FAILURE);
        }
        resultado += *suma;

        free(suma);
    }

    printf("\n\nResultado final de la suma: %.4f\n", resultado);
    return 0;

}