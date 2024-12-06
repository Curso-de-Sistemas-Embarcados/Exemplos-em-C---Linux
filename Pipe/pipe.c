#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

int main() {

    int  pid, /* pid do processo filho */
    fd[2], /* descritores do pipe */
    estado; /* estado do processo filho */
    char mensagem[30];
    
    /* cria o pipe */
    if (pipe(fd) < 0)
    { 
        printf("Erro na criação do pipe\n"); 
        exit(1);
    } 
    
    /* cria o processo */
    if ((pid = fork()) < 0)
    { 
        printf("Erro na criação do processo\n"); 
        exit(1);
    } 
    
    /* codigo do filho */
    if (pid == 0)
    {
        if (read(fd[0], mensagem, 30) < 0) 
            printf("Erro na leitura\n");
        else
            printf("Valor lido = %s\n", mensagem);

        exit(0); 
    }

    /* codigo do pai */
    strcpy(mensagem, "Mensagem de TESTE no PIPE");
    if (write(fd[1], mensagem, sizeof(mensagem)) < 0)
        printf("erro na escrita\n"); 
    wait(&estado);
    exit(0); 
}







