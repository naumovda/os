#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char *argv[]){
    int fd;

    if (argc < 2) {
        fprintf(stderr, "Invalid number of arguments\n" );
        return 1;
    }

    fd = open( argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0440 );
    if ( fd == -1 ) {
        fprintf( stderr, "Can not create file (%s)\n", argv[1] );
        return 1;
    }

    close(fd);
    printf("File created (%s)\n", argv[1] );
    return 0;
}
