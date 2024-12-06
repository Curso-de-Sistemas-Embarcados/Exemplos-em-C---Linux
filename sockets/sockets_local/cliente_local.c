#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main (int argc, char* const argv[]) {
	char socket_name[50];
	char mensagem[1024];

	int socket_id;
	struct sockaddr name;
	int length;

	if (argc < 3) {
		printf("Modo de Uso:\n ./cliente <caminho_do_socket> <mensagem>\n Exemplo: ./cliente /tmp/socket1 \"Mensagem de teste\"\n");
		exit(1);
	}
	else {
		strcpy(socket_name, argv[1]);
		strcpy(mensagem, argv[2]);
	}

	// Abrir Socket
	socket_id = socket(PF_LOCAL, SOCK_STREAM,0);

	// CONNECT
	name.sa_family = AF_LOCAL;
	strcpy(name.sa_data, socket_name);

	connect(socket_id, &name, sizeof(name));

	length = strlen(mensagem) + 1;
	write(socket_id, &length, sizeof(length));
	write(socket_id, mensagem, length);

	close(socket_id);
	return 0;
}