#include <signal.h>
#include <stdio.h>

sig_atomic_t sig_occured = 0;

void sig_handler (int snum)
{
    sig_occured = 1;
}

int main (void)
{
    struct sigaction act;

    sigemptyset (&act.sa_mask);

    act.sa_handler = &sig_handler;
    act.sa_flags = 0;

    if (sigaction (SIGINT, &act, NULL) == -1) {
        fprintf (stderr, "sigaction() error\n");
        return 1;
    }

    while (1) {
        if (sig_occured) {
            fprintf (stderr, "signal...\n");
            sig_occured = 0;
        }
    }

    return 0;
}