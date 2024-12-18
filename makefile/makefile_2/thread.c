#include "thread.h"
#include "sensor.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Função executada pela thread
void *thread_func(void *arg) {
    while (1) {
        int dado = ler_sensor();
        printf("Dado do sensor: %d\n", dado);
        sleep(1); // Aguarda 1 segundo entre cada impressão
    }
    return NULL;
}

void inicializar_thread() {
    pthread_t thread_id;

    // Cria a thread que executa a função thread_func
    if (pthread_create(&thread_id, NULL, thread_func, NULL) != 0) {
        perror("Erro ao criar a thread");
        return;
    }

    // A thread será executada em paralelo, mas precisamos que o programa principal espere por ela
    pthread_detach(thread_id);
}