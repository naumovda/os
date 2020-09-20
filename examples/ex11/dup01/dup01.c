#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#define FILENAME	"myfile"

int main (void)
{
	char ch;
	int fd = open (FILENAME, O_WRONLY | O_CREAT |
				O_TRUNC, 0640);
	if (fd == -1) {
		fprintf (stderr, "open() error\n");
		return 1;
	}

	if (dup2 (fd, 1) == -1) {
		fprintf (stderr, "dup2() error\n");
		return 1;
	}

	printf ("Hello World!\n");

	close (fd);
	return 0;
}
