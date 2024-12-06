#include <stdio.h>
#include <signal.h>
#include <unistd.h>
int main() {
    signal(SIGCHLD,SIG_IGN) ; /* ignora o sinal SIGCLD */
    if (fork() != 0) 
    	while(1) {
    		sleep(1);
    	}
    return(0);
}