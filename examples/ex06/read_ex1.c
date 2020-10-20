/* Вывод на экран файла, заданного в командной строке */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char *argv[]){
    #define BUFSIZE 100 /* Размер буфера для чтени я и записи данных */

    char buf[ BUFSIZE + 1 ]; /* Размер буфера для чтения и записи данных */
    int nb, i; /* число считанных байтов и параметр цикла */
    int fd; /* дескриптор читаемого файла */

    if (argc < 2) {
        fprintf( stderr, "File not specified\n" );
        return 1;
    }

    fd = open( argv[1], O_RDONLY );
    if ( fd == -1 ) {
        fprintf( stderr, "Can not open file (%s)\n", argv[1] );
        return 2;
    }

    printf( "============== File %s ================\n", argv[1] );

    while ( ( nb = read( fd, buf, BUFSIZE ) ) > 0 )
        if ( write( STDOUT_FILENO, buf, nb ) != nb) {
            fprintf( stderr, "%s: Writing error\n", argv[1] );
            return 3;
    }

    printf( "=================== EOF ===================\n" );
    close(fd);

    return 0;
}
