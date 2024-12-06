// Exemplo do Concorrência em Threads

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Função que incrementa o Contador
void* incrementa_contador (void *arg) {
	unsigned int i;
	for (i=0; i < 100; i++) {
		puts("Inicia   ++");
		usleep(random() % 100000);
		puts("Finaliza ++");
	}
	return NULL;
}
// Função que decrementa o Contador
void* decrementa_contador (void *arg) {
	unsigned int i;
	for (i=0; i < 100; i++) {
		puts("Inicia   --");
		usleep(random() % 100000);
		puts("Finaliza --");
	}
	return NULL;
}
int main (int argc, char** argv) {

	pthread_t t0;
	pthread_t t1;

	int res0, res1;

	res0 = pthread_create(&t0, NULL, incrementa_contador, NULL);
	res1 = pthread_create(&t1, NULL, decrementa_contador, NULL);

	res0 = pthread_join(t0, NULL);
	res0 = pthread_join(t1, NULL);

	puts("Terminou!");
	return 0;
}