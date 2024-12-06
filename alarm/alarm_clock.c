#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/signal.h>

void alarm_handler(int signum){
    printf("Buzz Buzz Buzz\n");
    
    alarm(1); //Novo alarme de 1 segundo
}

int main(){
    
    signal(SIGALRM, alarm_handler); //Configura o tratamento do alarme
    
    alarm(1); // Define o Alarme inicial
    
    while(1){
        pause(); // Aguarda um sinal
    }
}