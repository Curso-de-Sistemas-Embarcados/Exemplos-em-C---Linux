#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>
#include "shared_queue.h"

#define SHM_NAME "/shared_memory"
#define SEM_MUTEX "/sem_mutex"
#define SEM_EMPTY "/sem_empty"
#define SEM_FULL "/sem_full"

int main() {
    // Abrir memória compartilhada
    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("Erro ao abrir memória compartilhada");
        exit(1);
    }

    shared_queue *queue = mmap(NULL, sizeof(shared_queue), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (queue == MAP_FAILED) {
        perror("Erro ao mapear memória compartilhada");
        exit(1);
    }

    // Abrir semáforos
    sem_t *mutex = sem_open(SEM_MUTEX, 0);
    sem_t *empty = sem_open(SEM_EMPTY, 0);
    sem_t *full = sem_open(SEM_FULL, 0);

    if (mutex == SEM_FAILED || empty == SEM_FAILED || full == SEM_FAILED) {
        perror("Erro ao abrir semáforos");
        exit(1);
    }

    // Consumir itens
    for (int i = 0; i < 20; i++) {
        sem_wait(full);           // Espera item disponível
        sem_wait(mutex);          // Bloqueia a região crítica

        // Remover item da fila
        int item = queue->buffer[queue->out];
        printf("Consumidor: Removeu %d\n", item);
        queue->out = (queue->out + 1) % MAX_ITEMS;
        queue->count--;

        sem_post(mutex);          // Libera a região crítica
        sem_post(empty);          // Sinaliza espaço disponível

        sleep(2); // Simular tempo de consumo
    }

    // Limpeza
    munmap(queue, sizeof(shared_queue));
    sem_close(mutex);
    sem_close(empty);
    sem_close(full);

    return 0;
}