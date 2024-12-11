#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void cleanup(void *arg) {
    printf("Cleanup: liberando recurso %s\n", (char *)arg);
}

void *thread_func(void *arg) {
    pthread_cleanup_push(cleanup, "Recurso A");
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

    for (int i = 0; i < 10; i++) {
        printf("Trabalhando... %d\n", i);
        sleep(1);
        pthread_testcancel(); // Verifica solicitação de cancelamento
    }

    pthread_cleanup_pop(1); // Executa cleanup
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, thread_func, NULL);

    sleep(3);
    printf("Enviando cancelamento...\n");
    pthread_cancel(thread);

    pthread_join(thread, NULL);
    printf("Thread cancelada.\n");

    return 0;
}