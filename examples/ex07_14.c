#include <stdio.h>
#include <wait.h>
#include <unistd.h>
#include <sys/types.h>

int main (void)
{
    pid_t status, childpid;
    
    int exit_status;
    
    status = fork ();
    
    if (status == -1) {
        fprintf (stderr, "Fork error\n");
        return 1;
    }

/* Child */
    if (status == 0) {
        execlp ("sleep", "sleep", "30", NULL);
        fprintf (stderr, "Exec error\n");
        return 1;
    }

    /* Parent */
    childpid = wait (&exit_status);
    
    if (WIFEXITED (exit_status)) {
        printf ("Process with PID=%d "
            "has exited with code=%d\n", childpid,
            WEXITSTATUS (exit_status));
    }

    if (WIFSIGNALED (exit_status)) {
        printf ("Process with PID=%d "
        "has exited with signal.\n", childpid);
    }
    
    return 0;
}