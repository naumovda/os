#include <stdio.h>
#include <pthread.h>

#define A_COUNT 10
#define B_COUNT 25
#define C_COUNT 10

void * print_b (void * arg)
{
    int i;

    for (i = 0; i < B_COUNT; i++) {
        fprintf (stderr, "B");
        sleep (1);
    }

    fprintf (stderr, "(end-of-B)\n");
    return NULL;
}

void * print_c (void * arg)
{
    pthread_t thread = * (pthread_t *) arg;
    int i;
    
    for (i = 0; i < C_COUNT; i++) {
        fprintf (stderr, "C");
        sleep (1);
    }

    fprintf (stderr, "(end-of-C)\n");
    pthread_join (thread, NULL);

    return NULL;
}

int main (void)
{
    pthread_t thread1, thread2;
    int i;

    if (pthread_create (&thread1, NULL, &print_b, NULL) != 0) {
        fprintf (stderr, "Error (thread1)\n");
        return 1;
    }

    if (pthread_create (&thread2, NULL, &print_c, &thread1) != 0) {
        fprintf (stderr, "Error (thread2)\n");
        return 1;
    }

    for (i = 0; i < A_COUNT; i++) {
        fprintf (stderr, "A");
        sleep (1);
    }

    fprintf (stderr, "(end-of-A)\n");
    pthread_join (thread2, NULL);
    fprintf (stderr, "(end-of-all)\n");

    return 0;
}