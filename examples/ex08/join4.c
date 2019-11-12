#include <stdio.h>
#include <pthread.h>

void * any_func (void * arg)
{
    pthread_t thread = * (pthread_t *) arg;
    
    if (pthread_equal (pthread_self(), thread) != 0)
        fprintf (stderr, "1\n");
    
    return NULL;
}

int main (void)
{
    pthread_t thread;
    
    if (pthread_create (&thread, NULL, &any_func, &thread) != 0) {
        fprintf (stderr, "Error\n");
        return 1;
    }

    if (pthread_equal(pthread_self(), thread) != 0)
        fprintf (stderr, "2\n");
    
    pthread_join (thread, NULL);
    
    return 0;
}