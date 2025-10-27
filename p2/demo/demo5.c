#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void * th_function (void *arg)
{
    /**
     Es conveniente usar largos con los identificadores de hebra, concretamente pthead_t es un unsigned long int (%lu)
	 y esta definido en el fichero de cabecera pthreadtypes.h de la distribucion de linux concreta, por ejemplo en 
	 /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h
    **/	 

	printf("Soy la hebra %lu\n", (unsigned long) pthread_self());
	printf("Soy la hebra %lu\n", pthread_self());
	
	printf("Soy la hebra %ld\n", (long int) pthread_self());
	printf("Soy la hebra %ld\n", pthread_self());
	
	long * y = malloc(sizeof(long));
	*y = 10;
	
	//Para devolver algo de una hebra hay que usar pthread_exit(), NO se usa return.
	pthread_exit((void *)y); 
}


int main(int argn, char ** argp)
{
	int join_value;
	long rvalue;
	long *ret;
	pthread_t thread;

    // A esta hebra no se le pasa nada como parámetro, de ahí el NULL al final.
	if( pthread_create(&thread, NULL, (void *) th_function, NULL) )
    {
	  fprintf(stderr, "Error creating thread\n");
	  exit(EXIT_FAILURE); 
	}

	/* A pthread_join() le estamos pasando por referencia como segundo parámetro, la dirección
	de un puntero a entero. Al pasar la dirección de memoria de un puntero por referencia, el contenido
	de ese puntero (a donde apunta) puede ser modificado. ¿Con qué se modifica? Con la dirección de
	memoria de un entero que se devuelve en "pthread_exit((void *)y)". 
	
	Por tanto, "long * ret" ahora apunta a donde apuntaba "long * y", solo que está casteado a void.*/
	join_value = pthread_join(thread,(void**) &ret);

	if(join_value!=0)
	{
	  perror("Fallo en pthread_join()...\n");		
	  exit(EXIT_FAILURE);
	}
	  
	rvalue = *ret; 
	printf("Proceso ligero o hilo principal: El valor devuelto por la hebra %lu es: %ld\n", thread, rvalue);

	exit(EXIT_SUCCESS);
}
