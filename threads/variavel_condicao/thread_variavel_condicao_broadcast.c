#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5

pthread_mutex_t mutex;
pthread_cond_t cond;
int count = 0;        // Contador de threads que alcançaram a barreira
int barrier_limit;    // Número de threads necessário para liberar a barreira

void *thread_function(void *arg) {
    int thread_id = *(int *)arg;

    printf("Thread %d: trabalhando...\n", thread_id);
    sleep(rand() % 3 + 1); // Simula trabalho

    // Atinge a barreira
    pthread_mutex_lock(&mutex);

    count++;
    printf("Thread %d: atingiu a barreira (count = %d)\n", thread_id, count);

    if (count == barrier_limit) {
        // Última thread a alcançar a barreira sinaliza todas as outras
        printf("Thread %d: liberando todas as threads!\n", thread_id);
        pthread_cond_broadcast(&cond);
        count = 0; // Reinicia o contador para reutilizar a barreira
    } else {
        // Outras threads esperam na barreira
        pthread_cond_wait(&cond, &mutex);
        printf("Thread %d: liberada da barreira\n", thread_id);
    }

    pthread_mutex_unlock(&mutex);

    // Continua a execução
    printf("Thread %d: continuando o trabalho...\n", thread_id);
    sleep(rand() % 3 + 1); // Simula mais trabalho

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    barrier_limit = NUM_THREADS;

    // Inicializa o mutex e a variável de condição
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    // Cria as threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
    }

    // Aguarda todas as threads terminarem
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroi o mutex e a variável de condição
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    printf("Todas as threads concluíram.\n");

    return 0;
}