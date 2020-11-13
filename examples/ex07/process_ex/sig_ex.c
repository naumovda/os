#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    pid_t cpid;
    int status;

    switch (cpid = fork())
    {
    case -1:
        perror("fork");
        return -1;

    case 0:
        printf("Created child (PID = %d)\n", getpid());
        if (argc == 2){
            exit(atoi(argv[1]));
        }
        else {
            pause();
        }
        exit(EXIT_FAILURE);

    default:
        if (waitpid(cpid, &status, WUNTRACED | WCONTINUED) == -1){
            perror("waitpid");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status)){
            printf("Child process exited with status %d\n",
                    WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status)){
            printf("Child killed by signal %s\n",
                    strsignal(WTERMSIG(status)));
        }
        else if (WIFSTOPPED(status)){
            printf("Child stopped by signal %s\n",
                    strsignal(WSTOPSIG(status)));
        }

        exit(EXIT_SUCCESS);
    }
}
