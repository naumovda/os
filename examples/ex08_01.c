#include <stdio.h>
#include <unistd.h>

int main (void)
{
    int a = 10;
    pid_t status = fork ();

    /* Child */
    if (!status) {
        a++;
        printf ("Child's a=%d\n", a);
        return 0;
    }
    
    /* Parent */
    wait ();
    printf ("Parent's a=%d\n", a);    
    return 0;
}