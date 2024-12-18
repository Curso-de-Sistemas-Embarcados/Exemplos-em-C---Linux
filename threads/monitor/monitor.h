#ifndef MONITOR_H
#define MONITOR_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5

typedef struct {
    int buffer[BUFFER_SIZE];
    int count;  // Número de itens no buffer
    int in;     // Índice de inserção
    int out;    // Índice de remoção
    pthread_mutex_t mutex;
    pthread_cond_t cond_not_full;
    pthread_cond_t cond_not_empty;
} Monitor;

// Inicializa o monitor
void monitor_init(Monitor *q);

// Destrói o monitor
void monitor_destroy(Monitor *q);

// Insere um item no buffer
void monitor_enqueue(Monitor *q, int item);

// Remove um item do buffer
int monitor_dequeue(Monitor *q);

#endif