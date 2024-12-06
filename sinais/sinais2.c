#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void funcao_sigsegv() {
	printf("Recebi segmentation fault. Vou encerrar!!!\n");   
	exit(1);
}

int main() {
  char *p;
  signal(SIGSEGV, funcao_sigsegv);
  /* vou forcar um segment fault */
  printf("%s", *p);
}