#include <stdio.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define SEM_KEY 2007
#define MM_FILENAME "message"

int main (void)
{
	int fd, sem_id, buf_len;
	struct sembuf sb[1];
	char * mbuf;
	struct stat st;

	sem_id = semget (SEM_KEY, 1, 0600);
	if (sem_id == -1) {
		fprintf (stderr, "semget() error\n");
		return 1;
	}

	fd = open (MM_FILENAME, O_RDONLY);
	if (fd == -1) {
		fprintf (stderr, "Cannot open file\n");
		return 1;
	}

	if (fstat (fd, &st) == -1) {
		fprintf (stderr, "fstat() error\n");
		return 1;
	}

	buf_len = st.st_size;

	mbuf = mmap (0, buf_len, PROT_READ,
			MAP_SHARED, fd, 0);
	if (mbuf == MAP_FAILED) {
		fprintf (stderr, "mmap() error\n");
		return 1;
	}

	close (fd);
	write (1, mbuf, buf_len);
	printf ("\n");
	munmap (mbuf, buf_len);

	sb[0].sem_num = 0;
	sb[0].sem_flg = SEM_UNDO;
	
	sb[0].sem_op = 1;
	semop (sem_id, sb, 1);
	
	return 0;
}
