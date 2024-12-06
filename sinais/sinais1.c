#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void funcao_sigusr1()
{
    printf("Recebi o sinal SIGUSR1\n");  
}

void funcao_sigusr2()
{
    printf("Recebi o sinal SIGUSR2\n");  
}

int main()
{
    signal(SIGUSR1, funcao_sigusr1);
    signal(SIGUSR2, funcao_sigusr2);
    // kill(getpid(), SIGUSR1);
    // kill(getpid(), SIGUSR2);
    while(1) {sleep(1);}
}






