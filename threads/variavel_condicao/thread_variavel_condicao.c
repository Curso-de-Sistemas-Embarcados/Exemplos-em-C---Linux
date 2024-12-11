#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0;

pthread_mutex_t mutex;
pthread_cond_t condicao_produz;
pthread_cond_t condicao_consome;

void *produtor(void *arg) {
    while (1) {
        // Produz um item (simulado com um número aleatório)
        int item = rand() % 100;

        // Bloqueia o mutex para acessar o buffer
        pthread_mutex_lock(&mutex);

        // Espera até que haja espaço no buffer
        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&condicao_produz, &mutex);
        }

        // Insere o item no buffer
        buffer[count++] = item;
        printf("Produtor: produziu %d (buffer: %d/%d)\n", item, count, BUFFER_SIZE);

        // Sinaliza ao consumidor que há itens disponíveis
        pthread_cond_signal(&condicao_consome);

        // Desbloqueia o mutex
        pthread_mutex_unlock(&mutex);

        sleep(1); // Simula tempo de produção
    }
    return NULL;
}

void *consumidor(void *arg) {
    while (1) {
        // Bloqueia o mutex para acessar o buffer
        pthread_mutex_lock(&mutex);

        // Espera até que haja itens no buffer
        while (count == 0) {
            pthread_cond_wait(&condicao_consome, &mutex);
        }

        // Remove um item do buffer
        int item = buffer[--count];
        printf("Consumidor: consumiu %d (buffer: %d/%d)\n", item, count, BUFFER_SIZE);

        // Sinaliza ao produtor que há espaço disponível
        pthread_cond_signal(&condicao_produz);

        // Desbloqueia o mutex
        pthread_mutex_unlock(&mutex);

        sleep(2); // Simula tempo de consumo
    }
    return NULL;
}

int main() {
    pthread_t thread_produtor, thread_consumidor;

    // Inicializa o mutex e as variáveis de condição
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&condicao_produz, NULL);
    pthread_cond_init(&condicao_consome, NULL);

    // Cria as threads do produtor e do consumidor
    pthread_create(&thread_produtor, NULL, produtor, NULL);
    pthread_create(&thread_consumidor, NULL, consumidor, NULL);

    // Aguarda as threads (neste caso, o programa não terminará)
    pthread_join(thread_produtor, NULL);
    pthread_join(thread_consumidor, NULL);

    // Destroi o mutex e as variáveis de condição
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condicao_produz);
    pthread_cond_destroy(&condicao_consome);

    return 0;
}