/*
En nuestro programa, antes de hacer fork, creamos una variable y un puntero que apunte a esta misma variable. De esta forma, una vez que se ejecuta el fork, el valor almacenado en el puntero se mantiene, luego ¿podemos modificar la variable en el padre? Después de probar el código en clase descubrimos lo siguiente:

-Nada impide al hijo cambiar el valor, y es efectivo dentro del hijo.
-Sin embargo, la modificación no se refleja en el proceso padre.
-Aún así, el valor del puntero es idéntico en el padre y el hijo.

Como no teníamos ni idea de lo que estaba ocurriendo, decidimos preguntar en Internet:
Aquí el enlace a la pregunta en Stack Overflow (http://stackoverflow.com/questions/26534613/about-pointers-after-fork). 

Realmente ambos valores son idénticos, la diferencia radica en la forma de gestionar la memoria por el núcleo. En realidad esta dirección de memoria es una memoria virtual, la cual es idéntica (que no compartida) en ambos procesos (por eso el puntero sigue funcionando sin problema).
Sin embargo, esta memoria virtual, una vez el hijo trata de modificar la variable, se redirige a una dirección de memoria física diferente, de ahí que no se reflejen los cambios en el proceso padre. Parece ser una mecánica propia del kernel Linux que puede variar en otros sistemas UNIX y que aumenta el rendimiento de fork().
*/

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

int main (){
    int value = 0;
    int * pointer = &value;
    int status;

    pid_t pid;

    printf("Parent: Initial value is %d\n",value);

    pid = fork();

    switch(pid){
    case -1: //Error (maybe?)
        printf("Fork error, WTF?\n");
        exit(-1);

    case 0: //Child process
        printf("\tChild: I'll try to change the value\n\tChild: The pointer value is %p\n",pointer);
        (*pointer) = 1;
        printf("\tChild: I've set the value to %d\n",(*pointer));

        exit(EXIT_SUCCESS);
        break;
    }

    while(pid != wait(&status)); //Wait for the child process

    printf("Parent: the pointer value is %p\nParent: The value is %d\n",pointer,value);

    return 0;
}
