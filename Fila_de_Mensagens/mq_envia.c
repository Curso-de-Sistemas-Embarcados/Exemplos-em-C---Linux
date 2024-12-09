#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
 
#define QUEUE_PERMISSIONS 0660
#define MQ_MAX_MESSAGES 10
#define MQ_MAX_MSG_SIZE 128
#define MQ_MSG_BUFFER_SIZE MQ_MAX_MSG_SIZE + 10
 
int main(int argc, char **argv)
{
    mqd_t mqd_sender;
    struct mq_attr attr;
    const char *mq_name = "/mq-minha-fila";
    char tx_buffer[MQ_MSG_BUFFER_SIZE] = {"Mensagem de Dados - "};
     
    attr.mq_flags = 0;
    attr.mq_maxmsg = MQ_MAX_MESSAGES;
    attr.mq_msgsize = MQ_MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;
     
    if((mqd_sender = mq_open(mq_name, O_WRONLY | O_CREAT, QUEUE_PERMISSIONS, &attr)) == (mqd_t)-1)
    {
        perror("Cliente: mq_open");
        exit(1);
    }
     
    for(int i=0;i<10;i++)
    {
        sprintf(&tx_buffer[20], "%d", i);
        printf("Escritor: enviando mensagem: [%s]\n", tx_buffer);
        
        if(mq_send(mqd_sender, &tx_buffer[0], strlen (tx_buffer), 0) == (mqd_t)-1)
        {
            perror("Escritor: Unable to send message");
        }
    }
    if(mq_close(mqd_sender) == (mqd_t)-1)
    {
        perror("Escritor: mq_close");
        exit(1);
    }
    printf("Escritor: Exit\n");
    exit(0);
}