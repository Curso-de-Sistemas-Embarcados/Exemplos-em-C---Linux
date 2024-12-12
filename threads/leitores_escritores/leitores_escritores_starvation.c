#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_READERS 10
#define NUM_WRITERS 1

pthread_rwlock_t rwlock;
int shared_data = 0; // Recurso compartilhado

void* reader(void* arg) {
    int id = *(int*)arg;
    while (1) {
        pthread_rwlock_rdlock(&rwlock); // Leitura protegida
        printf("Leitor %d leu o valor: %d\n", id, shared_data);
        usleep(100000); // Simula atraso (100ms)
        pthread_rwlock_unlock(&rwlock); // Libera o bloqueio
    }
    return NULL;
}

void* writer(void* arg) {
    int id = *(int*)arg;
    while (1) {
        pthread_rwlock_wrlock(&rwlock); // Escrita protegida
        shared_data += 1;
        printf("Escritor %d atualizou o valor para: %d\n", id, shared_data);
        pthread_rwlock_unlock(&rwlock); // Libera o bloqueio
        usleep(500000); // Simula atraso (500ms)
    }
    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int ids[NUM_READERS > NUM_WRITERS ? NUM_READERS : NUM_WRITERS];

    pthread_rwlock_init(&rwlock, NULL);

    for (int i = 0; i < NUM_READERS; i++) {
        ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &ids[i]);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &ids[i]);
    }

    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    pthread_rwlock_destroy(&rwlock);
    return 0;
}