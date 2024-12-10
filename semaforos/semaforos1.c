#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>

#define SHM_NAME "/shared_mem_example"
#define SEM_NAME "/semaphore_example"
#define BUFFER_SIZE 256

int main() {
    // Criar memória compartilhada
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("Erro ao criar memória compartilhada");
        exit(1);
    }
    
    // Ajustar o tamanho da memória compartilhada
    if (ftruncate(shm_fd, BUFFER_SIZE) == -1) {
        perror("Erro ao ajustar tamanho da memória compartilhada");
        exit(1);
    }
    
    // Mapear memória compartilhada
    char *shared_mem = mmap(0, BUFFER_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shared_mem == MAP_FAILED) {
        perror("Erro ao mapear memória compartilhada");
        exit(1);
    }
    
    // Criar ou abrir o semáforo
    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0666, 1); // Inicializado com 1
    if (sem == SEM_FAILED) {
        perror("Erro ao criar semáforo");
        exit(1);
    }
    
    // Exemplo de uso (produtor e consumidor)
    pid_t pid = fork();
    
    if (pid == 0) { // Processo filho (produtor)
        sem_wait(sem); // Espera o semáforo
        snprintf(shared_mem, BUFFER_SIZE, "Olá do processo filho! PID: %d", getpid());
        printf("Filho escreveu: %s\n", shared_mem);
        sem_post(sem); // Libera o semáforo
    } else if (pid > 0) { // Processo pai (consumidor)
        sleep(1); // Aguardar o processo filho
        sem_wait(sem); // Espera o semáforo
        printf("Pai leu: %s\n", shared_mem);
        sem_post(sem); // Libera o semáforo
        wait(NULL); // Aguarda o filho terminar
    } else {
        perror("Erro ao criar processo");
        exit(1);
    }
    
    // Limpar recursos
    munmap(shared_mem, BUFFER_SIZE);
    shm_unlink(SHM_NAME);
    sem_close(sem);
    sem_unlink(SEM_NAME);

    return 0;
}