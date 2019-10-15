#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

#define WORKTIME 3

int main (void)
{
    unsigned long parents = 0;
    unsigned long children = 0;

    pid_t result;
    
    time_t nowtime = time (NULL);
    
    result = fork ();
    
    if (!result) 
    {
        while (time (NULL) < nowtime + WORKTIME) 
            children++;
        printf ("children: %ld\n", children);
    } 
    else 
    {
        while (time (NULL) < nowtime + WORKTIME) 
            parents++;
        printf ("parents: %ld\n", parents);
    }
    
    return 0;
}