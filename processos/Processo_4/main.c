#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int novo_processo(char * programa, char ** lista_de_argumentos){
	pid_t pid_filho;
	pid_filho = fork();
	if (pid_filho != 0)
		return pid_filho;
	else {
		execvp(programa, lista_de_argumentos);
		printf("Erro no EXEC\n");
		abort();
	}
}

int main() {
	char * lista_de_argumentos[] = { "ls", "-l", "/", NULL};
	novo_processo("ls", lista_de_argumentos);
	printf("Este é o processo PAI\n");
	return 0;
}