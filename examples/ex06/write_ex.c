#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char *argv[]){
    if (argc < 2){
        fprintf(stderr, "File not pecified\n");
        return -1;
    }

    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1){
        perror("open");
        return -1;
    }

    char buf[255];
    ssize_t nread, nwrite;
    while ((nread = read(STDIN_FILENO, buf, sizeof buf)) > 0){
        buf[nread] = 0;
        nwrite = write(fd, buf, strlen(buf));
        if (nwrite == -1){
            perror("write");
            return -1;
        }
    }
    if (nread == -1){
        perror("read");
        return -1;
    }

    printf("%s: written successfully\n", argv[1]);

    return 0;
}
