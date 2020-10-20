#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main (int argc, char ** argv)
{
    int year;

    if (argc < 2) {
        fprintf (stderr, "child: too few arguments\n");
        return 2;
    }

    year = atoi (argv[1]);

    if (year <= 0)
        return 2;
    
    if ( ((year%4 == 0) && (year%100 != 0)) || (year%400 == 0) )
        kill (getppid (), SIGUSR1);
    else
        kill (getppid (), SIGUSR2);
        
    return 0;
}