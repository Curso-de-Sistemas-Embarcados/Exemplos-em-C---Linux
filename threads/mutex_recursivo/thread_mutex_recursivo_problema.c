#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t mutex;

void recursive_function(int count) {
    if (count <= 0) return;

    // Tenta bloquear o mutex
    pthread_mutex_lock(&mutex);
    printf("Bloqueio do mutex na recursão: %d\n", count);

    // Chamada recursiva
    recursive_function(count - 1);

    // Desbloqueia o mutex
    pthread_mutex_unlock(&mutex);
}

int main() {
    // Inicializa o mutex com atributos padrão (PTHREAD_MUTEX_NORMAL)
    pthread_mutex_init(&mutex, NULL);

    printf("Executando com PTHREAD_MUTEX_NORMAL (comportamento padrão):\n");

    // Isso causará um deadlock ou comportamento indefinido
    recursive_function(3);

    // Destroi o mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}