#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    // Abre o acesso à área de memória compartilhada como Leitura
    int shm_fd = shm_open("/shm_example", O_RDONLY, 0666);

    // Mapeia a memória para espaço interno do programa
    char *ptr = (char *)mmap(0, 4096, PROT_READ, MAP_SHARED, shm_fd, 0);

    // Lê dados da memória compartilhada
    printf("Message from shared memory: %s\n", ptr);

    // Remove o mapeamento de memória e fecha o acesso ao arquivo
    munmap(ptr, 4096);
    close(shm_fd);

    // Remove área compartilhada
    shm_unlink("/shm_example"); 
    return 0;
}