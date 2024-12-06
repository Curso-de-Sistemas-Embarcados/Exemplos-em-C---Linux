#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/signal.h>

void nullfcn() /* define-se aqui uma funcao executada quando */
{ } /* o sinal SIGALRM e interceptado por signal() */
/* esta funcao nao faz absolutamente nada */

/* dorme por secs segundos */
void sleep2(int secs) 
{
    if( signal(SIGALRM,nullfcn) )
    {
        perror("error: reception signal") ;
        exit(-1) ; }
    alarm(secs) ; /* inicializa o relogio a secs segundos */
    pause(); /* processo em espera por um sinal */
}

int main() /* so para testar sleep2() */
{
    if(fork()==0)
    {
        sleep(3) ;
        printf("hello, sleep\n") ;
    }
    else /* pai */
    {
        sleep2(3) ;
        printf("hello, sleep2\n") ;
    }
    return 0;
}