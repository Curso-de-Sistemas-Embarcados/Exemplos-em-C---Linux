#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main() {
	signal(SIGCHLD, SIG_IGN);
    if (fork() != 0) 
    	while(1) {
    		sleep(1);
    	}
    return(0);
}