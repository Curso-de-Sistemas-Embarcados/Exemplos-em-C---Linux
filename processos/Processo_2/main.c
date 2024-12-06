#include <stdlib.h>

int main () {
	int retorna_valor;
	retorna_valor = system("ls -l /");
	return retorna_valor;
}