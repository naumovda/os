#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

void print_statistics (const char * fname, struct stat * st)
{
    printf ("FILE:\t\t%s\n", fname);
    printf ("UID:\t\t%d\n", (int) st->st_uid);
    printf ("GID:\t\t%d\n", (int) st->st_gid);
    printf ("SIZE:\t\t%ld\n", (long int) st->st_size);
    printf ("AT:\t\t%s", ctime (&st->st_atime));
    printf ("MT:\t\t%s", ctime (&st->st_mtime));
}

int main (int argc, char ** argv)
{
    struct stat st;

    if (argc < 2) {
        fprintf (stderr, "Too few arguments\n");
        return 1;
    }

    if (stat (argv[1], &st) == -1) {
        fprintf (stderr, "stat() error\n");
        return 1;
    }

    printf ("-- STAT() --\n");
    print_statistics (argv[1], &st);

    if (lstat (argv[1], &st) == -1) {
        fprintf (stderr, "lstat() error\n");
        return 1;
    }
    
    printf ("-- LSTAT() --\n");
    print_statistics (argv[1], &st);
    
    return 0;
}