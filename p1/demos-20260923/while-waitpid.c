/****************************************************************
Esquema de espera de hijos usando waitpid()

Puede abrir otro terminal y experimentar usando: 

prompt$ kill -SIGSTOP id_proceso     -> Para parar un proceso
prompt$ kill -SIGCONT id_proceso     -> Para reanudar un proceso

Si se usa wait() no podrá detectar que un proceso se ha parado
o se ha reanudado, solo puede detectarlo con waitpid()
*****************************************************************/
...
...

/*Espera del padre a los hijos*/
//-1 hace que se espere a cualquier hijo, WUNTRACED es la macro que indica que detecte estados de parada y reanudación
while ( (childpid=waitpid(-1, &status, WUNTRACED)) > 0 ) 
{
     if (WIFEXITED(status)) 
     {
        printf("Proceso Padre %d, hijo con PID %ld finalizado, status = %d\n", getpid(), (long int)childpid, WEXITSTATUS(status));
     } 
     else if (WIFSIGNALED(status))  
     {
        printf("Proceso Padre %d, hijo con PID %ld finalizado al recibir la señal %d\n", getpid(), (long int)childpid, WTERMSIG(status));
     } 
     else if (WIFSTOPPED(status))  //Para cuando se para un proceso. Con wait() no nos serviria.
     {
        printf("Proceso Padre %d, hijo con PID %ld PARADO al recibir la señal %d\n", getpid(), (long int)childpid,WSTOPSIG(status));
     } 
     else if (WIFCONTINUED(status))  //Para cuando se reanuda un proceso parado. Con wait() no nos serviria.
     {
        printf("Proceso Padre %d, hijo con PID %ld REANUDADO\n", getpid(), (long int) childpid);		  
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


