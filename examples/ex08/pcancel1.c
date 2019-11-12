#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void * any_func (void * arg)
{
    while (1) {
        fprintf (stderr, ".");
        sleep (1);
    }
   
    return NULL;
}

int main (void)
{
    pthread_t thread;

    if (pthread_create (&thread, NULL, &any_func, NULL) != 0) {
        fprintf (stderr, "Error\n");
        return 1;
    }

    sleep (5);

    pthread_cancel (thread);

    if (!pthread_equal (pthread_self (), thread))
        pthread_join (thread, NULL);
    
    fprintf (stderr, "\n");
    
    return 0;
}