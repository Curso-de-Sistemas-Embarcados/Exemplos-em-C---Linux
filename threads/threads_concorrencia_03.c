// Exemplo do Concorrência em Threads

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

volatile int varCompartilhada=0;

static pthread_mutex_t mutexLock;

// Função que incrementa o Contador
void* incrementa_contador (void *arg) {
	for (unsigned int i=0; i < 10000; i++) {
		pthread_mutex_lock(&mutexLock);
		varCompartilhada++;
		pthread_mutex_unlock(&mutexLock);
	}
	return NULL;
}

// Função que decrementa o Contador
void* decrementa_contador (void *arg) {
	for (unsigned int i=0; i < 10000; i++) {
		pthread_mutex_lock(&mutexLock);
		varCompartilhada--;
		pthread_mutex_unlock(&mutexLock);
	}
	return NULL;
}

int main (int argc, char** argv) {

	pthread_t t0;
	pthread_t t1;

	int res, res0, res1;

	res = pthread_mutex_init(&mutexLock, NULL);

	res0 = pthread_create(&t0, NULL, incrementa_contador, NULL);
	res1 = pthread_create(&t1, NULL, decrementa_contador, NULL);
	res0 = pthread_join(t0, NULL);
	res0 = pthread_join(t1, NULL);

	pthread_mutex_destroy(&mutexLock);

	printf("Valor final: %d\n", varCompartilhada);
	return 0;
}