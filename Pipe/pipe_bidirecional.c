#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 100

int main() {
    int pipe_pai_para_filho[2];  // Pipe para comunicação de pai para filho
    int pipe_filho_para_pai[2];  // Pipe para comunicação de filho para pai
    pid_t pid;
    char mensagem_pai[] = "Mensagem do pai!";
    char mensagem_filho[] = "Mensagem do filho!";
    char buffer[BUFFER_SIZE];

    // Cria pipes
    if (pipe(pipe_pai_para_filho) == -1 || pipe(pipe_filho_para_pai) == -1) {
        perror("Erro na criação do pai");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid < 0) {
        perror("Falha no fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // Processo filho
        // Fecha pipe não usado
        close(pipe_pai_para_filho[1]);  // Close unused write end of parent-to-child pipe
        close(pipe_filho_para_pai[0]);  // Close unused read end of child-to-parent pipe

        // Lê mensagem do pai
        read(pipe_pai_para_filho[0], buffer, BUFFER_SIZE);
        printf("Filho recebe: %s\n", buffer);

        // Envia mensagem de resposta ao pai
        write(pipe_filho_para_pai[1], mensagem_filho, strlen(mensagem_filho) + 1);

        // Fecha pipe não usado
        close(pipe_pai_para_filho[0]);
        close(pipe_filho_para_pai[1]);

    } else {  // Processo pai
        // Fecha pipe não usado
        close(pipe_pai_para_filho[0]);  // Close unused read end of parent-to-child pipe
        close(pipe_filho_para_pai[1]);  // Close unused write end of child-to-parent pipe

        // Envia mensagem para o filho
        write(pipe_pai_para_filho[1], mensagem_pai, strlen(mensagem_pai) + 1);

        // Lê resposta do filho
        read(pipe_filho_para_pai[0], buffer, BUFFER_SIZE);
        printf("Pai recebe: %s\n", buffer);

        // Fecha pipe não usado
        close(pipe_pai_para_filho[1]);
        close(pipe_filho_para_pai[0]);
    }

    return 0;
}