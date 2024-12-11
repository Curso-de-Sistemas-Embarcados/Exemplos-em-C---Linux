#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "monitor.h"

Monitor queue;

// Função do produtor
void *producer(void *arg) {
    for (int i = 0; i < 10; i++) {
        int item = rand() % 100;
        monitor_enqueue(&queue, item);
        sleep(rand() % 2); // Simula tempo de produção
    }
    return NULL;
}

// Função do consumidor
void *consumer(void *arg) {
    for (int i = 0; i < 10; i++) {
        int item = monitor_dequeue(&queue);
        sleep(rand() % 3); // Simula tempo de consumo
    }
    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;

    // Inicializa o monitor
    monitor_init(&queue);

    // Cria threads produtoras e consumidoras
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Aguarda as threads terminarem
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Destrói o monitor
    monitor_destroy(&queue);

    printf("Execução finalizada.\n");
    return 0;
}