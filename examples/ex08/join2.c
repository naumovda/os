#include <stdio.h>
#include <pthread.h>

void * any_func (void * arg)
{
    int a = *(int *) arg;
    a++;
    return (void *) a;
}

int main (void)
{
    pthread_t thread;
    int parg = 2007, pdata;

    if (pthread_create (&thread, NULL, &any_func, &parg) != 0) {
        fprintf (stderr, "Error\n");
        return 1;
    }

    pthread_join (thread, (void *) &pdata);
    
    printf ("%d\n", pdata);
    
    return 0;
}