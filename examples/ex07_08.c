#include <stdio.h>
#include <unistd.h>

extern char ** environ;

int main (void)
{
    char * uname_args[] = {
        "uname",
        "-a",
        NULL
    };

    execve ("/bin/uname", uname_args, environ);
    
    fprintf (stderr, "Error\n");
    
    return 0;
}