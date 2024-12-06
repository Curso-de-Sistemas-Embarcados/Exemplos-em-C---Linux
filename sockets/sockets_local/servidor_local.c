// Servidor Local
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>

char socket_name[50];// = argv[1];
int socket_id;

void sigint_handler(int signum){
  printf("Desligando o Servidor!\n");
  signal(SIGINT, SIG_DFL);
  unlink(socket_name);
  close(socket_id);
  exit(0);
}

int servidor (int client_socket)
{
  while (1) {
    int length;
    char* text;
    if (read (client_socket, &length, sizeof (length)) == 0)
      return 0;
    text = (char*) malloc (length);
    read (client_socket, text, length);
    fprintf (stderr,"%s\n", text);
    if (!strcmp (text, "sair"))
      return 1;
    free (text);
  } 
}

int main (int argc, char* const argv[]) {
	int cliente_solicita_encerramento = 0;
	
	struct sockaddr socket_struct;

	if (argc < 2) {
		printf("Modo de Uso:\n ./servidor <caminho_do_socket> \n Exemplo: ./servidor /tmp/socket1\n");
		exit(1);
	}
	else
		strcpy(socket_name, argv[1]);

  	//Define o Tratamento de SIGINT
  	signal(SIGINT, sigint_handler);
	
	// Abrir SOCKET
	socket_id = socket(PF_LOCAL, SOCK_STREAM, 0);

	// BIND
	socket_struct.sa_family = AF_LOCAL;
	strcpy(socket_struct.sa_data, socket_name);

	bind(socket_id, &socket_struct, sizeof(socket_struct));

	// LISTEN
	listen(socket_id, 10);

	while(!cliente_solicita_encerramento) {
		struct sockaddr cliente;
		int socket_id_cliente;
		socklen_t cliente_len;

		socket_id_cliente = accept(socket_id, &cliente, &cliente_len);

		cliente_solicita_encerramento = servidor(socket_id_cliente);

		close(socket_id_cliente);
	}
	unlink(socket_name);
	close(socket_id);
	
	return 0;
}