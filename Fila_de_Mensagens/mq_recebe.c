#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
 
#define MQ_QUEUE_PERMISSIONS 0660
#define MQ_MAX_MESSAGES 10
#define MQ_MAX_MSG_SIZE 128
#define MQ_MSG_BUFFER_SIZE MQ_MAX_MSG_SIZE + 10
 
int main (int argc, char **argv)
{
	mqd_t mqd_receiver, mqd_test;
	const char *escritor_queue = "/mq-minha-fila";
	struct mq_attr attr;
	char rx_buffer[MQ_MSG_BUFFER_SIZE];
	 
	attr.mq_flags = 0;
	attr.mq_maxmsg = MQ_MAX_MESSAGES;
	attr.mq_msgsize = MQ_MAX_MSG_SIZE;
	attr.mq_curmsgs = 0;
	 
	if((mqd_receiver = mq_open(escritor_queue, O_RDONLY | O_CREAT, MQ_QUEUE_PERMISSIONS, &attr)) == (mqd_t)-1)
	{
		perror("Leitor: mq_open (leitor)");
		exit(1);
	}
	int i=10;
	while(i)
	{
		printf("Leitor: bloqueado aguardando chegada de mensagens...\n");
		
		if(mq_receive (mqd_receiver, rx_buffer, MQ_MSG_BUFFER_SIZE, NULL) == (mqd_t)-1)
		{
			perror("Leitor: mq_receive");
			exit(1);
		}
		else
		{
			printf("Leitor: mensagem recebida: [%s]\n", rx_buffer);
			i--;
		}
	}
	if(mq_close(mqd_receiver) == (mqd_t)-1)
	{
		perror("Leitor: mq_close (leitor)");
		exit(1);
	}
	printf("Leitor: Exit\n");
	exit(0);
}