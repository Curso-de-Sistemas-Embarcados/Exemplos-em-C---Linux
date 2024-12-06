#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int fd;
    char * minhafifo = "/tmp/minha_fifo";
    
    /* cria FIFO (pipe com nome) */
    mkfifo(minhafifo, 0666);
    
    /* escreve "Ola" na FIFO */
    fd = open(minhafifo, O_WRONLY);
    write(fd, "Ola", sizeof("Ola"));
    close(fd);
    
    /* Apaga a FIFO */
    unlink(minhafifo);
    
    return 0;
}