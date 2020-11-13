#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>


int main(){
    int fd = open("test1", O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (fd == -1){
        perror("open");
        return -1;
    }

    printf("No O_APPEND flag\n");
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags & O_WRONLY){
        printf("file in write mode\n");
    }
    if (flags & O_APPEND){
        printf("file in append mode\n");
    }

    printf("\nSetting O_APPEND flag...\n");

    flags |= O_APPEND;
    if (fcntl(fd, F_SETFL, flags) == -1){
        perror("fcntl");
        return -1;
    }

    flags = fcntl(fd, F_GETFL, 0);
    if (flags & O_WRONLY){
        printf("file in write mode\n");
    }
    if (flags & O_APPEND){
        printf("file in append mode\n");
    }

    return 0;
}
