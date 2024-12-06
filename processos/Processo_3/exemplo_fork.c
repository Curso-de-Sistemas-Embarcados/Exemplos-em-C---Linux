#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main ()
{
    pid_t child_pid;
    printf ("PID do PAI: %d\n", (int) getpid ());
    child_pid = fork ();
    if (child_pid != 0) {
        printf ("Este é o processo PAI, PID %d\n", (int) getpid());
        printf ("O PID do meu filho é %d\n", (int) child_pid);
    }
    else
        printf ("Este é o processo FILHO, PID %d\n", (int) getpid());
    return 0;
}