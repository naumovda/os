#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>


int main(int argc, char *argv[]){
    if (argc < 2){
        fprintf(stderr, "File not specified\n");
        return -1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1){
        perror("open");
        return -1;
    }

    struct stat buf;
    if (fstat(fd, &buf) == -1){
        perror("stat");
        return -1;
    }

    printf("File: %s\n", argv[1]);
    printf("Type: ");
    switch (buf.st_mode & S_IFMT) {
    case S_IFBLK:
        printf("block device\n");
        break;
    case S_IFCHR:
        printf("character device\n");
        break;
    case S_IFDIR:
        printf("directory\n");
        break;
    case S_IFIFO:
        printf("FIFO/pipe\n");
        break;
    case S_IFLNK:
        printf("symlink\n");
        break;
    case S_IFREG:
        printf("regular file\n");
        break;
    case S_IFSOCK:
        printf("socket\n");
        break;
    default:
        printf("unknown?\n");
        break;
    }
    printf("Hard links: %lu\n", buf.st_nlink);
    printf("Owner UID: %u\n", buf.st_uid);
    printf("Size in bytes: %ld\n", buf.st_size);
    printf("Last access: %s\n", ctime(&buf.st_atime));

    return 0;
}
