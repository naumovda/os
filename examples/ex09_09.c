#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <fcntl.h>

int main (int argc, char ** argv)
{
    struct stat st;
    int fd;

    if (argc < 2) {
        fprintf (stderr, "Too few arguments\n");
        return 1;
    }

    fd = open (argv[1], O_RDONLY);
    if (fd == -1) {
        fprintf (stderr, "Cannot open file (%s)\n", argv[1]);
        return 1;
    }
    
    if (fstat (fd, &st) == -1) {
        fprintf (stderr, "stat() error\n");
        return 1;
    }

    printf ("FILE:\t\t%s\n", argv[1]);
    printf ("UID:\t\t%d\n", (int) st.st_uid);
    printf ("GID:\t\t%d\n", (int) st.st_gid);
    printf ("SIZE:\t\t%ld\n", (long int) st.st_size);
    printf ("AT:\t\t%s", ctime (&st.st_atime));
    printf ("MT:\t\t%s", ctime (&st.st_mtime));

    close (fd);
    return 0;
}