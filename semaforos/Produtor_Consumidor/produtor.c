#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>
#include "shared_queue.h"

#define SHM_NAME "/shared_memory"
#define SEM_MUTEX "/sem_mutex"
#define SEM_EMPTY "/sem_empty"
#define SEM_FULL "/sem_full"

int main() {
    // Criar ou abrir memória compartilhada
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("Erro ao criar memória compartilhada");
        exit(1);
    }
    ftruncate(shm_fd, sizeof(shared_queue));
    
    shared_queue *queue = mmap(NULL, sizeof(shared_queue), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (queue == MAP_FAILED) {
        perror("Erro ao mapear memória compartilhada");
        exit(1);
    }

    // Inicializar a fila compartilhada (apenas no primeiro uso)
    memset(queue, 0, sizeof(shared_queue));

    // Abrir semáforos
    sem_t *mutex = sem_open(SEM_MUTEX, O_CREAT, 0666, 1);
    sem_t *empty = sem_open(SEM_EMPTY, O_CREAT, 0666, MAX_ITEMS);
    sem_t *full = sem_open(SEM_FULL, O_CREAT, 0666, 0);

    if (mutex == SEM_FAILED || empty == SEM_FAILED || full == SEM_FAILED) {
        perror("Erro ao abrir semáforos");
        exit(1);
    }

    // Produzir itens
    for (int i = 0; i < 20; i++) {
        sem_wait(empty);          // Espera espaço disponível
        sem_wait(mutex);          // Bloqueia a região crítica

        // Inserir item na fila
        queue->buffer[queue->in] = i;
        printf("Produtor: Inseriu %d\n", i);
        queue->in = (queue->in + 1) % MAX_ITEMS;
        queue->count++;

        sem_post(mutex);          // Libera a região crítica
        sem_post(full);           // Sinaliza item disponível

        sleep(1); // Simular tempo de produção
    }

    // Limpeza
    munmap(queue, sizeof(shared_queue));
    sem_close(mutex);
    sem_close(empty);
    sem_close(full);

    return 0;
}