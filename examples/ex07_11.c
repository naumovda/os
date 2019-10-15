#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

extern char ** environ;

int main (void)
{
    pid_t result;

    char * sleep_args[] = {
        "sleep",
        "5",
        NULL
    };

    result = fork ();

    if (result == -1) 
    {
        fprintf (stderr, "fork error\n");
        return 1;
    }

    if (result == 0) 
    {
        execve ("/bin/sleep", sleep_args, environ);
        fprintf (stderr, "execve error\n");
        return 1;
    } 
    else 
    {
        fprintf (stderr, "I'm parent with PID=%d\n", getpid());
    }
    
    return 0;
}