/* testa os valores de retorno de alarm() */
/* assim que seu funcionamento */
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

/* rotina executada na recepcao de SIGALRM */
void int_trata_alarme(int sig) { 
  	printf("recepcaao do sinal %d :SIGALRM\n",sig); 
}

int main() {

  unsigned sec;
  signal(SIGALRM,int_trata_alarme); /* interceptacao do sinal */
  printf("Fazendo alarm(5)\n");
  sec = alarm(5);
  printf("Valor retornado por alarm: %d\n",sec) ;
  printf("Principal em loop infinito (CTRL+c para acabar)\n") ;

  while(1) {
  	sleep(6);
  	alarm(3);
  }
}