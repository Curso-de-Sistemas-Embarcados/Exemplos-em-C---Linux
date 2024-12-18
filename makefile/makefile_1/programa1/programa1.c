#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Programa 1: Inicializando programa 2...\n");
    if (fork() == 0) {
        execl("./programa2/programa2", "programa2", NULL);
        perror("Erro ao iniciar programa 2");
    }
    return 0;
}