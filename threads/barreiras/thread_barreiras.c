#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 10

pthread_barrier_t barrier;

void* thread_work(void* arg) {
    int id = *(int*)arg;
    printf("Thread %d: Fazendo trabalho inicial...\n", id);
    usleep(rand() % 1000000); // Simula trabalho inicial com atraso aleatório

    printf("Thread %d: Aguardando na barreira...\n", id);
    pthread_barrier_wait(&barrier); // Sincronização na barreira

    printf("Thread %d: Continuando após a barreira.\n", id);
    free(arg);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    // Inicializa a barreira para NUM_THREADS threads
    pthread_barrier_init(&barrier, NULL, NUM_THREADS);

    // Cria as threads
    for (int i = 0; i < NUM_THREADS; i++) {
        int* id = malloc(sizeof(int)); // Para evitar conflitos com IDs
        *id = i + 1;
        pthread_create(&threads[i], NULL, thread_work, id);
    }

    // Aguarda a finalização de todas as threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroi a barreira
    pthread_barrier_destroy(&barrier);

    return 0;
}