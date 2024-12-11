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
    pthread_mutexattr_t attr;

    // Inicializa os atributos do mutex
    pthread_mutexattr_init(&attr);

    // Define o mutex como recursivo
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

    // Inicializa o mutex com os atributos
    pthread_mutex_init(&mutex, &attr);

    // Destroi os atributos após inicializar o mutex
    pthread_mutexattr_destroy(&attr);

    printf("Executando com PTHREAD_MUTEX_RECURSIVE:\n");

    // Isso funcionará corretamente
    recursive_function(3);

    // Destroi o mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}