#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main(){
    printf("Main process PID = %d\n", getpid());
    pid_t cpid;
    switch (cpid = fork()){
        case -1:
            perror("fork");
            return -1;

        case 0:
            printf("(child) Child process PID = %d\n", getpid());
            printf("(child) Parent process PID = %d\n", getppid());
            break;

        default:
            printf("(parent) Child process PID = %d\n", cpid);
            printf("(parent) Parent process PID = %d\n", getpid());
    }

    return 0;
}
