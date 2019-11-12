#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main (void)
{
    pid_t result = fork ();

    if (result == -1) {
        fprintf (stderr, "Fork error\n");
        return 1;
    }

    /* Child */
    if (result == 0) {
        execlp ("ls", "ls", "/", NULL);
        fprintf (stderr, "Exec error\n");
        return 1;
    }
    
    /* Parent */
    sleep (3);
    
    fprintf (stderr, "I'm parent\n");
    
    return 0;
}