#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main (int argc, char ** argv)
{
	int pf[2];
	int pid1, pid2;

	if (argc < 3) {
		fprintf (stderr, "Too few arguments\n");
		return 1;
	}

	if (pipe (pf) == -1) {
		fprintf (stderr, "pipe() error\n");
		return 1;
	}

	if ((pid1 = fork ()) == 0) {
		dup2 (pf[1], 1);
		close (pf[0]);
		execlp ("ls", "ls", argv[1], NULL);
		fprintf (stderr, "exec() [1] error\n");
		return 1;
	}

	if ((pid1 = fork ()) == 0) {
		dup2 (pf[0], 0);
		close (pf[1]);
		execlp ("grep", "grep", "-i", argv[2], NULL);
		fprintf (stderr, "exec() [2] error\n");
		return 1;
	}

	close (pf[1]);
	waitpid (pid1, NULL, 0);
	close (pf[0]);
	waitpid (pid2, NULL, 0);
	return 0;
}
