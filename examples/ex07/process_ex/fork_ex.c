#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main(){
    pid_t procid;

    switch (procid = fork()){
    case -1:
        perror("fork");
        return -1;

    case 0:
        printf("Created child process\n");
        break;

    default:
        sleep(1);
    }

    printf("%s process PID = %d\n", (procid == 0) ? "Child" : "Parent",
           getpid());

    return 0;
}
