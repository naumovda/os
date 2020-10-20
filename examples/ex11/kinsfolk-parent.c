#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int main (int argc, char ** argv)
{
    pid_t cpid;
    int status;
    
    if (argc < 2) {
        fprintf (stderr, "Too few arguments\n");
        return 1;
    }
    
    cpid = fork();
    
    if (!cpid) {
        execl ("./kinsfolk-child1", "Child", argv[1], NULL);
        fprintf (stderr, "execl() error\n");
        return 1;
    }

    waitpid (cpid, &status, 0);

    if (WIFEXITED (status)) {
        if (WEXITSTATUS (status) == 1)
            printf ("%s: leap year\n", argv[1]);
        else if (WEXITSTATUS (status) == 0)
            printf ("%s: not leap year\n", argv[1]);
        else {
            fprintf (stderr, "error: unexpected return code\n");
            return 1;
        }
    }
    
    return 0;
}