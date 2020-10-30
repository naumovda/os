#include <stdio.h>
#include <unistd.h>

int main(){
    printf("Program started\n");

    execlp("ls", "ls", "-l", (char *) NULL);

    printf("This line will never be reached\n");

    return 0;
}
