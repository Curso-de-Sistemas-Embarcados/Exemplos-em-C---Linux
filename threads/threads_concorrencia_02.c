// Exemplo do Concorrência em Threads

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

//#define SEQUENCIAL

volatile int varCompartilhada=0;

// Função que incrementa o Contador
void* incrementa_contador (void *arg) {
	for (unsigned int i=0; i < 10000; i++) {
		varCompartilhada++;
	}
	return NULL;
}

// Função que decrementa o Contador
void* decrementa_contador (void *arg) {
	for (unsigned int i=0; i < 10000; i++) {
		varCompartilhada--;
	}
	return NULL;
}

int main (int argc, char** argv) {

	pthread_t t0;
	pthread_t t1;

	int res0, res1;

#ifdef SEQUENCIAL
	res0 = pthread_create(&t0, NULL, incrementa_contador, NULL);
	res0 = pthread_join(t0, NULL);
	res1 = pthread_create(&t1, NULL, decrementa_contador, NULL);
	res0 = pthread_join(t1, NULL);
#else
	res0 = pthread_create(&t0, NULL, incrementa_contador, NULL);
	res1 = pthread_create(&t1, NULL, decrementa_contador, NULL);
	res0 = pthread_join(t0, NULL);
	res0 = pthread_join(t1, NULL);
#endif
	printf("Valor final: %d\n", varCompartilhada);
	return 0;
}