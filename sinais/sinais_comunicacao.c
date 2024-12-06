#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
void it_fils()
{
  printf("[%d] Processo filho recebe sinal SIGUSR1 e envia para si mesmo!\n", getpid()) ;
  kill (getpid(),SIGINT) ;
}

void fils()
{
  signal(SIGUSR1,it_fils) ;
  printf("[%d] Processo filho iniciado!\n", getpid()) ;
  while(1);
}

int main() {

  int pid ;
  if ((pid=fork())==0) 
    fils();
  else {
    sleep(2) ;
    printf("[%d] Processo Pai executando apos o Fork.\n", getpid());
    kill (pid,SIGUSR1) ;
    sleep(1);
  }
  
  printf("[%d] Processo Pai encerrando.\n", getpid());
  exit(0); 
}