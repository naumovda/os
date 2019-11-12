#include <stdio.h>
#include <pthread.h>

struct thread_arg
{
    char * str;
    int num;
};

void * any_func (void * arg)
{
    struct thread_arg targ = (struct thread_arg *) arg;

    fprintf (stderr, "str=%s\n", targ->str);
    fprintf (stderr, "num=%d\n", targ->num);

    return NULL;
}

int main (void)
{
    pthread_t thread;
    int result;

    struct thread_arg targ;
    targ.str = "Hello World";
    targ.num = 2007;

    result = pthread_create (&thread, NULL, &any_func, &targ);

    while (1);

    return 0;
}