#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(){
    char buf[] = "Kitty is smart";
    char *bp = buf;
    size_t size = strlen(buf);
    ssize_t nwrite;

    while(size != 0 && (nwrite = write(STDOUT_FILENO, bp, 1)) > 0){
        if (nwrite == -1){
            perror("write");
            return -1;
        }
        size -= nwrite;
        bp += nwrite;
    }
    printf("\n");

    return 0;
}
