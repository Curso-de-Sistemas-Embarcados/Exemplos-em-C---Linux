#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/wait.h>

#define SEM_NAME "/db_pool_semaphore"
#define NUM_CONNECTIONS 5
#define NUM_PROCESSES 10

void simulate_database_access(int process_id) {
    printf("Processo %d: Conexão adquirida! Trabalhando...\n", process_id);
    sleep(2); // Simula trabalho no banco de dados
    printf("Processo %d: Liberando conexão.\n", process_id);
}

void child_process(int process_id) {
    sem_t *sem;

    // Abre o semáforo nomeado existente
    sem = sem_open(SEM_NAME, 0);
    if (sem == SEM_FAILED) {
        perror("sem_open falhou");
        exit(EXIT_FAILURE);
    }

    printf("Processo %d: Tentando adquirir uma conexão...\n", process_id);

    // Tenta adquirir o semáforo
    sem_wait(sem);

    // Simula acesso ao banco de dados
    simulate_database_access(process_id);

    // Libera o semáforo
    sem_post(sem);

    // Fecha o semáforo
    sem_close(sem);

    exit(0);
}

int main() {
    sem_t *sem;
    pid_t pids[NUM_PROCESSES];
    int i;

    // Cria o semáforo nomeado com valor inicial igual ao número de conexões
    sem = sem_open(SEM_NAME, O_CREAT | O_EXCL, 0644, NUM_CONNECTIONS);
    if (sem == SEM_FAILED) {
        perror("sem_open falhou");
        exit(EXIT_FAILURE);
    }

    // Cria múltiplos processos paralelos
    for (i = 0; i < NUM_PROCESSES; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork falhou");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Processo filho
            child_process(i);
        } else {
            // Processo pai
            pids[i] = pid;
        }
    }

    // Aguarda todos os processos filhos terminarem
    for (i = 0; i < NUM_PROCESSES; i++) {
        waitpid(pids[i], NULL, 0);
    }

    // Remove o semáforo nomeado
    sem_unlink(SEM_NAME);

    printf("Todos os processos concluíram. Semáforo removido.\n");
    return 0;
}