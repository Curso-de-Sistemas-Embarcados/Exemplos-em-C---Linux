#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/signal.h>

void sigquit_handler(int signum){
  printf("Alarme Desligao\n");

  //Desliga todos os Alarmes
  alarm(0);

  // Redefine o tratamento de SIGINT
  // Agora Ctrl-C termina o programa
  signal(SIGINT, SIG_DFL);
}

void sigint_handler(int signum){
  printf("Alarme Adiado em 5 segundos!\n");

  //schedule next alarm for 5 seconds
  alarm(5);
}

void alarm_handler(int signum){
  printf("Buzz Buzz Buzz\n");

  //set a new alarm for 1 second
  alarm(1);
}

int main(){

  //Define o tratamento do alarme
  signal(SIGALRM, alarm_handler);

  //Define o Tratamento de SIGINT
  signal(SIGINT, sigint_handler);

  //Define o Tratamento de SIGQUIT
  signal(SIGQUIT, sigquit_handler);

  //Define o primeiro alarme
  alarm(1);

  //Pausa no Loop
  while(1){
    pause();
  }
}