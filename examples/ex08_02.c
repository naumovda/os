#include <stdio.h>
#include <unistd.h>

void * any_func (void * args)
{
    fprintf (stderr, "Hello World\n");
    sleep (5);
    return NULL;
}

int main (void)
{
    any_func (NULL);
    fprintf (stderr, "Goodbye World\n");
    while (1);
    return 0;
}