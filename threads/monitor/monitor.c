#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "monitor.h"

// Inicializa o monitor
void monitor_init(Monitor *q) {
    q->count = 0;
    q->in = 0;
    q->out = 0;
    pthread_mutex_init(&q->mutex, NULL);
    pthread_cond_init(&q->cond_not_full, NULL);
    pthread_cond_init(&q->cond_not_empty, NULL);
}

// Destrói o monitor
void monitor_destroy(Monitor *q) {
    pthread_mutex_destroy(&q->mutex);
    pthread_cond_destroy(&q->cond_not_full);
    pthread_cond_destroy(&q->cond_not_empty);
}

// Insere um item no buffer
void monitor_enqueue(Monitor *q, int item) {
    pthread_mutex_lock(&q->mutex);

    // Aguarda espaço no buffer
    while (q->count == BUFFER_SIZE) {
        pthread_cond_wait(&q->cond_not_full, &q->mutex);
    }

    // Insere o item no buffer
    q->buffer[q->in] = item;
    q->in = (q->in + 1) % BUFFER_SIZE;
    q->count++;

    printf("Produziu: %d (buffer: %d/%d)\n", item, q->count, BUFFER_SIZE);

    // Notifica os consumidores que há itens disponíveis
    pthread_cond_signal(&q->cond_not_empty);

    pthread_mutex_unlock(&q->mutex);
}

// Remove um item do buffer
int monitor_dequeue(Monitor *q) {
    pthread_mutex_lock(&q->mutex);

    // Aguarda itens no buffer
    while (q->count == 0) {
        pthread_cond_wait(&q->cond_not_empty, &q->mutex);
    }

    // Remove o item do buffer
    int item = q->buffer[q->out];
    q->out = (q->out + 1) % BUFFER_SIZE;
    q->count--;

    printf("Consumiu: %d (buffer: %d/%d)\n", item, q->count, BUFFER_SIZE);

    // Notifica os produtores que há espaço disponível
    pthread_cond_signal(&q->cond_not_full);

    pthread_mutex_unlock(&q->mutex);

    return item;
}