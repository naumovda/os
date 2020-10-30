#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    char *command[] = {
        "ps",
        "-e",
        NULL
    };

    switch (fork()){
        case -1:
            perror("fork");
            return -1;

        case 0:
            execvp(command[0], command);

        default:
            wait(0);
            return 0;
    }
}
