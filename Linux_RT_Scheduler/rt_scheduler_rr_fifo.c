#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/time.h>
#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>

#define MAX_PRIORITY 32

void *fifo_thread(void *arg) {
    struct sched_param param;
    param.sched_priority = MAX_PRIORITY - 1; // Prioridade alta, mas não a máxima

    if (sched_setscheduler(0, SCHED_FIFO, &param) == -1) {
        perror("sched_setscheduler FIFO falhou");
        pthread_exit(NULL);
    }

    printf("Thread FIFO iniciada com prioridade %d\n", param.sched_priority);

    while (1) {
        // Simula trabalho
        usleep(50000); // 50ms
        printf("FIFO\n");
    }

    pthread_exit(NULL);
}

void *rr_thread(void *arg) {
    struct sched_param param;
    param.sched_priority = MAX_PRIORITY - 2; // Prioridade menor que a FIFO

    if (sched_setscheduler(0, SCHED_RR, &param) == -1) {
        perror("sched_setscheduler RR falhou");
        pthread_exit(NULL);
    }

    printf("Thread RR iniciada com prioridade %d\n", param.sched_priority);

    while (1) {
        // Simula trabalho
        usleep(75000); // 75ms
        printf("RR\n");
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t fifo_tid, rr_tid;

    // Bloqueia paginação de memória para evitar falhas de tempo real
    if (mlockall(MCL_CURRENT | MCL_FUTURE) == -1) {
        perror("mlockall falhou");
        return 1;
    }

    // Cria as threads
    if (pthread_create(&fifo_tid, NULL, fifo_thread, NULL) != 0) {
        perror("pthread_create FIFO falhou");
        return 1;
    }

    if (pthread_create(&rr_tid, NULL, rr_thread, NULL) != 0) {
        perror("pthread_create RR falhou");
        return 1;
    }

    // Espera as threads terminarem (nunca acontecerá neste exemplo)
    pthread_join(fifo_tid, NULL);
    pthread_join(rr_tid, NULL);

    return 0;
}