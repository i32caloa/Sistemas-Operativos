#include <sys/types.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h>
#include <sys/wait.h>
#include <string.h> 

int main () 
{
    int i=0, j, status; 
    pid_t rf, childpid;

    rf = fork(); 
    switch (rf) 
    {
        case -1:        
            perror("fork error: "); //perror() consulta el valor actual de "errno" y muestra el mensaje correspondienteen inglés.
            printf("errno value= %d\n", errno); 
            exit(EXIT_FAILURE);

        case 0:
            printf("Soy el hijo, mi PID es %d y mi variable i, inicialmente vale: %d\n",getpid( ),i);

            for (j=0; j<5; j++)
            {
                i=i+2;                
                printf ("Soy el hijo, mi variable i vale: %d\n", i);
            }
   
            break; 

        default:
            printf("Soy el padre, mi PID es %d y mi variable i, inicialmente vale: %d\n", getpid( ), i);

            for (j=0; j<5; j++) 
            {
                i=i+2;               
                printf ("Soy el padre, mi variable i vale: %d\n", i);
            }
                  
             /*Espera del padre a los hijos*/
             //wait() no permite detectar la parada y reanudacion de procesos hijos: WIFSTOPPED(status), WIFCONTINUED(status)
             //Practique con el codigo proporcionado en el fichero "while-waitpid.c"
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
    }//switch
            
    
    //Esta linea la ejecuta tanto el padre como el hijo 
    printf ("Final de ejecucion... ¿QUIEN SOY?\n"); 
    exit(EXIT_SUCCESS);
}
