#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Mutexes compartilhados
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex3 = PTHREAD_MUTEX_INITIALIZER;

// Função para a Thread 1
void* thread_func1(void* arg) {
    printf("Thread 1: Tentando bloquear mutex1...\n");
    pthread_mutex_lock(&mutex1);
    printf("Thread 1: mutex1 bloqueado.\n");
    sleep(1);  // Simula algum trabalho

    printf("Thread 1: Tentando bloquear mutex2...\n");
    pthread_mutex_lock(&mutex2);
    printf("Thread 1: mutex2 bloqueado.\n");

    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);

    return NULL;
}

// Função para a Thread 2
void* thread_func2(void* arg) {
    printf("Thread 2: Tentando bloquear mutex1...\n");
    pthread_mutex_lock(&mutex1);
    printf("Thread 2: mutex1 bloqueado.\n");
    sleep(1);  // Simula algum trabalho

    printf("Thread 2: Tentando bloquear mutex2...\n");
    pthread_mutex_lock(&mutex2);
    printf("Thread 2: mutex2 bloqueado.\n");

    printf("Thread 2: Tentando bloquear mutex3...\n");
    pthread_mutex_lock(&mutex3);
    printf("Thread 2: mutex3 bloqueado.\n");

    pthread_mutex_unlock(&mutex3);
    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);

    return NULL;
}

// Função para a Thread 3
void* thread_func3(void* arg) {
    printf("Thread 3: Tentando bloquear mutex1...\n");
    pthread_mutex_lock(&mutex1);
    printf("Thread 3: mutex1 bloqueado.\n");
    sleep(1);  // Simula algum trabalho

    printf("Thread 3: Tentando bloquear mutex2...\n");
    pthread_mutex_lock(&mutex2);
    printf("Thread 3: mutex2 bloqueado.\n");

    printf("Thread 3: Tentando bloquear mutex3...\n");
    pthread_mutex_lock(&mutex3);
    printf("Thread 3: mutex3 bloqueado.\n");

    pthread_mutex_unlock(&mutex3);
    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);

    return NULL;
}

int main() {
    pthread_t thread1, thread2, thread3;

    // Cria as threads
    pthread_create(&thread1, NULL, thread_func1, NULL);
    pthread_create(&thread2, NULL, thread_func2, NULL);
    pthread_create(&thread3, NULL, thread_func3, NULL);

    // Aguarda o término das threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    // Destroi os mutexes
    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);
    pthread_mutex_destroy(&mutex3);

    return 0;
}