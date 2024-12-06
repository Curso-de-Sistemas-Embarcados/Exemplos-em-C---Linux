/* teste dos valores de retorno de alarm() quando 2
* chamadas a alarm() sao feitas sucessivamente
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

/* tratamento do desvio sobre SIGALRM */
void it_horloge(int sig) 
{
  printf("recepcao do sinal %d : SIGALRM\n",sig) ;
  printf("atencao, o principal reassume o comando\n") ;
}

/* tratamento do desvio sobre SIGALRM */
void it_quit(int sig) 
{
  printf("recepcao do sinal %d : SIGINT\n",sig) ;
  printf("Por que eu ?\n") ;
  signal(SIGINT,SIG_DFL);
}

int main() {

  unsigned sec ;
  signal(SIGINT,it_quit); /* interceptacao do ctrl-c */
  signal(SIGALRM,it_horloge); /* interceptacao do sinal de alarme */
  
  printf("Armando o alarme para 10 segundos\n");
  sec=alarm(10);

  printf("valor retornado por alarm: %d\n",sec) ;
  printf("Paciencia... Vamos esperar 3 segundos com sleep\n");
  
  sleep(3);
  printf("Rearmando alarm(5) antes de chegar o sinal precedente\n");
  
  sec=alarm(5);
  printf("novo valor retornado por alarm: %d\n",sec);
  printf("Principal em loop infinito (ctrl-c para parar)\n");
  
  for(;;);
    
}