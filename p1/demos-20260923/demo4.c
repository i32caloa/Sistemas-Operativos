#include <sys/types.h> 
#include <sys/wait.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <string.h> 

int main()
{

   pid_t idProceso, childpid;
   int status;
   /* Variable para comprobar que se copia inicialmente en cada proceso y
	que luego puede cambiarse independientemente en cada uno de ellos. */
   int var = 1;

   idProceso = fork();
   if (idProceso == -1)
   {
		perror("fork error: "); //perror() consulta el valor actual de "errno" y muestra el mensaje correspondienteen inglés.
		printf("errno value= %d\n", errno); 
		exit(EXIT_FAILURE);
   }
   else if (idProceso == 0)
   {
		/* El hijo escribe su pid en pantalla y el valor de variable */
		printf ("Hijo: mi PID es %d. El PPID de mi padre es %d\n", getpid(), getppid());
		
		/* Escribe valor de variable y la cambia */
		printf ("Hijo: valor de var = %d. Cambiando var a 2...\n", var); 
		var = 2;
		
		printf ("Hijo: termino con valor de var = %d\n", var);
		
		exit (33);
   }
   else //Padre
   {
		/* Espera un segundo (para dar tiempo al hijo a hacer sus cosas y no entremezclar salida en la pantalla) y escribe su pid y el de su hijo */
		/* Comente el sleep() y observe la salida por pantalla */
		/* OJO, ESTOS SLEEPS SON A MODO DIVULGATIVO. NO USAR SLEEPS PARA SINCRONIZAR SUS PROCESOS*/
		sleep (2);
		printf ("Padre: mi pid es %d. El pid de mi hijo es %d\n",getpid(), idProceso);
	
      /*Espera del padre a los hijos*/
      while ( (childpid=wait(&status)) > 0 ) 
      {
          if (WIFEXITED(status)) 
          {
            printf("Proceso Padre %d, hijo con PID %ld finalizado, status = %d\n", getpid(), (long int)childpid, WEXITSTATUS(status));
          } 
          else if (WIFSIGNALED(status))  
          {             
            printf("Proceso Padre %d, hijo con PID %ld finalizado al recibir la señal %d\n", getpid(), (long int)childpid, WTERMSIG(status));
          } 
      }//while

      if (childpid==(pid_t)-1 && errno==ECHILD)
      {
         printf("Proceso Padre %d, no hay mas hijos que esperar. Valor de errno = %d, definido como: %s\n", getpid(), errno, strerror(errno));
      }
      else
      {
         printf("Error en la invocacion de wait o waitpid. Valor de errno = %d, definido como: %s\n", errno, strerror(errno));
         exit(EXIT_FAILURE);
      }	 
      
      printf("Proceso Padre con PID %d, valor de var = %d\n", getpid(), var);
    
    }
	 exit(EXIT_SUCCESS);
}
