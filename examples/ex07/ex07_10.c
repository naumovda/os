#include <stdio.h>
#include <unistd.h>

int main (void)
{
    char * env_args[] = {
        "env",
        NULL
    };

    execve ("/usr/bin/env", env_args, NULL);

    fprintf (stderr, "Error\n");

    return 0;
}