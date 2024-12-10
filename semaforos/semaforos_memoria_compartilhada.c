#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SHM_NAME "/shared_mem_safe"
#define SEM_NAME "/semaphore_safe"
#define BUFFER_SIZE sizeof(int)

int main() {
    // Criar memória compartilhada
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("Erro ao criar memória compartilhada");
        exit(1);
    }
    
    // Ajustar tamanho da memória compartilhada
    if (ftruncate(shm_fd, BUFFER_SIZE) == -1) {
        perror("Erro ao ajustar tamanho da memória compartilhada");
        exit(1);
    }
    
    // Mapear memória compartilhada
    int *shared_counter = mmap(0, BUFFER_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shared_counter == MAP_FAILED) {
        perror("Erro ao mapear memória compartilhada");
        exit(1);
    }
    
    // Inicializar o contador na memória compartilhada
    *shared_counter = 0;

    // Criar ou abrir o semáforo
    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0666, 1); // Inicializado com 1
    if (sem == SEM_FAILED) {
        perror("Erro ao criar semáforo");
        exit(1);
    }

    // Criar dois processos
    pid_t pid1 = fork();
    if (pid1 == -1) {
        perror("Erro ao criar processo 1");
        exit(1);
    }

    if (pid1 == 0) { // Processo filho 1
        for (int i = 0; i < 100000; i++) {
            sem_wait(sem);       // Bloqueia o semáforo
            (*shared_counter)++; // Incrementa o contador
            sem_post(sem);       // Libera o semáforo
        }
        exit(0);
    }

    pid_t pid2 = fork();
    if (pid2 == -1) {
        perror("Erro ao criar processo 2");
        exit(1);
    }

    if (pid2 == 0) { // Processo filho 2
        for (int i = 0; i < 100000; i++) {
            sem_wait(sem);       // Bloqueia o semáforo
            (*shared_counter)++; // Incrementa o contador
            sem_post(sem);       // Libera o semáforo
        }
        exit(0);
    }

    // Processo pai espera os filhos terminarem
    wait(NULL);
    wait(NULL);

    // Mostrar o valor do contador
    printf("Valor final do contador: %d\n", *shared_counter);

    // Limpar recursos
    munmap(shared_counter, BUFFER_SIZE);
    shm_unlink(SHM_NAME);
    sem_close(sem);
    sem_unlink(SEM_NAME);

    return 0;
}