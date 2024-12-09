#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
    // Cria área de memória compartilhada
    int shm_fd = shm_open("/shm_exemplo", O_CREAT | O_RDWR, 0666);

    // Define tamanho da memória compartilhada
    ftruncate(shm_fd, 4096);

    // Mapeia a memória para espaço interno do programa
    char *ptr = (char *)mmap(0, 4096, PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // Escreve na área de memória compartilhada
    sprintf(ptr, "Mensagem na área de memória compartilhada!");


    printf("Mensagem escrita na área compartilhada.\n");

    // Remove o mapeamento de memória e fecha o acesso ao arquivo
    munmap(ptr, 4096);
    close(shm_fd);

    return 0;
}