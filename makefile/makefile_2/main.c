#include <stdio.h>
#include <unistd.h>

#include "sensor.h"
#include "thread.h"

int main() {
    // Inicializa o gerador de números aleatórios
    inicializar_sensor();

    // Inicializa a thread para imprimir os dados periodicamente
    inicializar_thread();

    // Mantém o programa principal rodando
    while (1) {
        // Pode adicionar lógica aqui se necessário
        sleep(10); // Aguarda 10 segundos antes de verificar novamente
    }

    return 0;
}