#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_BUF 1024

int main()
{
    int fd;
    char * minhafifo = "/tmp/minha_fifo";
    char buffer[MAX_BUF];
    
    /* abre e le a mensagem da FIFO */
    fd = open(minhafifo, O_RDONLY);
    read(fd, buffer, MAX_BUF);
    printf("Recebido: %s\n", buffer);
    close(fd);
    
    return 0;
}
