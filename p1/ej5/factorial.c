#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdint.h>

int main(int argc, char *argv[]){

    if(argc != 2){

        printf("Uso: %s <numero>\n", argv[0]);
        exit(EXIT_FAILURE);

    }

    uint8_t numero = atoi(argv[1]);
    uint32_t resultado = 0;

    if(numero != 0){

            resultado = 1;

    } else if(numero < 0){

        printf("No se puede hacer el factorial de %s", argv[1]);
        exit(EXIT_FAILURE);

    }

    for(int i = 1; i <= numero; i++){

        resultado *= i;        

    }

    printf("Resultado: %d\n", resultado);

    exit(EXIT_SUCCESS);

}