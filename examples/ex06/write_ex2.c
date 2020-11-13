#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char *argv[]){
    if (argc < 2){
        fprintf(stderr, "File not specified\n");
        return -1;
    }

    int fd = open(argv[1], O_WRONLY | O_APPEND);
    if (fd == -1){
        perror("open for append");
        return -1;
    }

    char msg[] = "test test test test test\n";
    size_t size = strlen(msg);
    ssize_t nwrite;

    nwrite = write(fd, msg, size);
    if (nwrite < size){
        printf("partial write\n");
    }
    if (nwrite == -1){
        perror("write");
        return -1;
    }

    return 0;
}
