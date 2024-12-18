#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Programa 2: Inicializando programa 3...\n");
    if (fork() == 0) {
        execl("./programa3/programa3", "programa3", NULL);
        perror("Erro ao iniciar programa 3");
    }
    return 0;
}