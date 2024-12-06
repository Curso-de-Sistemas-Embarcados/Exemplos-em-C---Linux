#include <stdio.h>
#include <unistd.h>

int main () {
	printf("O identificador do processo PID é: %d\n",
		(int) getpid());
	printf("O identificador do processo pai - PPID é: %d\n",
		(int) getppid());
	return 0;
}