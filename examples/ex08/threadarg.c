#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void * any_func (void * arg)
{
    int a = *(int*) arg;

    fprintf (stderr, "Hello World "
        "with argument=%d\n", a);

    return NULL;
}

int main (int argc, char ** argv)
{
    pthread_t thread;
    int arg, result;

    if (argc < 2) {
        fprintf (stderr, "Too few arguments\n");
        return 1;
    } 

    arg = atoi (argv[1]);
    result = pthread_create (&thread, NULL, &any_func, &arg);
    
    fprintf (stderr, "Goodbye World\n");
    while (1);
    
    return 0;
}