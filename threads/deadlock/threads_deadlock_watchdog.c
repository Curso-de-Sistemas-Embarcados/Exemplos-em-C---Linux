#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define TIMEOUT 5  // Tempo máximo (em segundos) para uma thread concluir sua execução

// Mutexes compartilhados
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex3 = PTHREAD_MUTEX_INITIALIZER;

// Variáveis de controle
volatile int thread1_status = 0;  // 0: Em execução, 1: Finalizada
volatile int thread2_status = 0;  // 0: Em execução, 1: Finalizada
volatile int thread3_status = 0;  // 0: Em execução, 1: Finalizada

void* thread_func1(void* arg) {
    printf("Thread 1: Tentando bloquear mutex1...\n");
    pthread_mutex_lock(&mutex1);
    printf("Thread 1: mutex1 bloqueado.\n");
    sleep(2);

    printf("Thread 1: Tentando bloquear mutex2...\n");
    pthread_mutex_lock(&mutex2);
    printf("Thread 1: mutex2 bloqueado.\n");
    sleep(2);

    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);
    printf("Thread 1: Finalizada.\n");

    thread1_status = 1;  // Marca como finalizada
    return NULL;
}

void* thread_func2(void* arg) {
    printf("Thread 2: Tentando bloquear mutex2...\n");
    pthread_mutex_lock(&mutex2);
    printf("Thread 2: mutex2 bloqueado.\n");
    sleep(2);

    printf("Thread 2: Tentando bloquear mutex3...\n");
    pthread_mutex_lock(&mutex3);
    printf("Thread 2: mutex3 bloqueado.\n");
    sleep(2);

    pthread_mutex_unlock(&mutex3);
    pthread_mutex_unlock(&mutex2);
    printf("Thread 2: Finalizada.\n");

    thread2_status = 1;  // Marca como finalizada
    return NULL;
}

void* thread_func3(void* arg) {
    printf("Thread 3: Tentando bloquear mutex3...\n");
    pthread_mutex_lock(&mutex3);
    printf("Thread 3: mutex3 bloqueado.\n");
    sleep(2);

    printf("Thread 3: Tentando bloquear mutex1...\n");
    pthread_mutex_lock(&mutex1);
    printf("Thread 3: mutex1 bloqueado.\n");
    sleep(2);

    pthread_mutex_unlock(&mutex1);
    pthread_mutex_unlock(&mutex3);
    printf("Thread 3: Finalizada.\n");

    thread3_status = 1;  // Marca como finalizada
    return NULL;
}

void* watchdog_func(void* arg) {
    time_t start_time = time(NULL);

    while (1) {
        sleep(1);  // Checa periodicamente
        time_t current_time = time(NULL);

        if (thread1_status && thread2_status && thread3_status) {
            printf("Watchdog: Todas as threads concluíram com sucesso.\n");
            break;
        }

        if (current_time - start_time > TIMEOUT) {
            printf("Watchdog: Timeout atingido! Liberando mutexes e reiniciando...\n");

            pthread_mutex_unlock(&mutex1);
            pthread_mutex_unlock(&mutex2);
            pthread_mutex_unlock(&mutex3);

            break;
        }
    }

    return NULL;
}

int main() {
    pthread_t thread1, thread2, thread3, watchdog;

    // Cria as threads de trabalho
    pthread_create(&thread1, NULL, thread_func1, NULL);
    pthread_create(&thread2, NULL, thread_func2, NULL);
    pthread_create(&thread3, NULL, thread_func3, NULL);

    // Cria a thread watchdog
    pthread_create(&watchdog, NULL, watchdog_func, NULL);

    // Aguarda o término das threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(watchdog, NULL);

    // Destroi os mutexes
    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);
    pthread_mutex_destroy(&mutex3);

    printf("Programa finalizado.\n");
    return 0;
}