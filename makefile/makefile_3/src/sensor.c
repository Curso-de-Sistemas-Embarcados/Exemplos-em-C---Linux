#include "sensor.h"
#include <stdlib.h>
#include <time.h>

void inicializar_sensor() {
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));
}

int ler_sensor() {
    // Gera um número aleatório entre 0 e 100 simulando a leitura do sensor
    return rand() % 101;
}