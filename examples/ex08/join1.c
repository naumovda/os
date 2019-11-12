#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define A_COUNT 15
#define B_COUNT 10

void * print_b (void * arg)
{
    int i;

    for (i = 0; i < B_COUNT; i++) {
        fprintf (stderr, "B");
        sleep (1);
    }

    fprintf (stderr, "C");
    return NULL;
}

int main (void)
{
    pthread_t thread;
    int i;
    
    if (pthread_create (&thread, NULL, &print_b, NULL) != 0) {
        fprintf (stderr, "Error\n");
        return 1;
    }

    for (i = 0; i < A_COUNT; i++) {
        fprintf (stderr, "A");
        sleep (1);
    }

    if (pthread_join (thread, NULL) != 0) {
        fprintf (stderr, "Join error\n");
        return 1;
    }
    
    fprintf (stderr, "D\n");
    
    return 0;
}