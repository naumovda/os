#include <stdio.h>
#include <sys/sem.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define SEM_KEY 	2007
#define MM_FILENAME 	"message"

union semnum {
	int val;
	struct semid_ds * buf;
	unsigned short * array;
} sem_arg;

int main (int argc, char ** argv)
{
	int fd, sem_id, msg_len;
	struct sembuf sb[1];
	unsigned short sem_vals[1];
	char * mbuf;		
	
	if (argc < 2) {
		fprintf (stderr, "Too few arguments\n");
		return 1;
	}
	
	msg_len = strlen (argv[1]);
	fd = open (MM_FILENAME, O_RDWR | O_CREAT |
			O_TRUNC, 0600);
	if (fd == -1) {
		fprintf (stderr, "Cannot open file\n");
		return 1;
	}

	mbuf = (char *) malloc (msg_len);
	if (mbuf == NULL) {
		fprintf (stderr, "malloc() error\n");
		return 1;
	}
	
	mbuf = memset (mbuf, 0, msg_len);
	write (fd, mbuf, msg_len);
	lseek (fd, 0, SEEK_SET);
	free (mbuf);
	
	mbuf = mmap (0, msg_len, PROT_WRITE | PROT_READ,
			MAP_SHARED, fd, 0);
	if (mbuf == MAP_FAILED) {
		fprintf (stderr, "mmap() error\n");
		return 1;
	}

	close (fd);
	strncpy (mbuf, argv[1], msg_len);
	msync (mbuf, msg_len, MS_SYNC);

	sem_id = semget (SEM_KEY, 1,
			0600 | IPC_CREAT | IPC_EXCL);
	if (sem_id == -1) {
		fprintf (stderr, "semget() error\n");
		return 1;
	}
	
	sem_vals[0] = 1;
	sem_arg.array = sem_vals;

	if (semctl (sem_id, 0, SETALL, sem_arg) == -1) {
		fprintf (stderr, "semctl() error\n");
		return 1;
	}

	sb[0].sem_num = 0;
	sb[0].sem_flg = SEM_UNDO;

	sb[0].sem_op = -1;
	semop (sem_id, sb, 1);
	
	sb[0].sem_op = -1;
	semop (sem_id, sb, 1);

	semctl (sem_id, 1, IPC_RMID, sem_arg);
	munmap (mbuf, msg_len);
	unlink (MM_FILENAME);
	return 0;
}
