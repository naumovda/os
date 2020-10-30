#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
    switch (fork())
    {
        case -1:
            perror("fork");
            return -1;

        case 0:
            printf("Created child process\n");
            exit(5);

        default:{
            int status;
            wait(&status);
            printf("Child process exited with status %d\n",
                   WEXITSTATUS(status));
        }
    }

    return 0;
}
