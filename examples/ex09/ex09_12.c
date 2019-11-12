#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define READLNK_BUF_SIZE 1024

char readlnk_buf [READLNK_BUF_SIZE+1];

void print_link_info (const char * fname)
{
    int count = readlink (fname, readlnk_buf, READLNK_BUF_SIZE);

    if (count == -1) {
        fprintf (stderr, "readlink() error\n");
        exit (1);
    }

    readlnk_buf [count] = '\0';

    printf ("%s --> %s", fname, readlnk_buf);
}

void print_stat (const char * fname)
{
    struct stat st;

    if (lstat (fname, &st) == -1) {
        fprintf (stderr, "lstat() error\n");
        exit (1);
    }

    if (S_ISDIR (st.st_mode))
        printf ("dir");
    else if (S_ISCHR (st.st_mode))
        printf ("chrdev");
    else if (S_ISBLK (st.st_mode))
        printf ("blkdev");
    else if (S_ISREG (st.st_mode))
        printf ("regfile");
    else if (S_ISFIFO (st.st_mode))
        printf ("fifo");
    else if (S_ISLNK (st.st_mode))
        print_link_info (fname);
    else if (S_ISSOCK (st.st_mode))
        printf ("socket");
    else
        printf ("unknown");

    printf (", %d\n", st.st_size);
}

int main (int argc, char ** argv)
{
    DIR * dir;
    struct dirent * entry;

    if (argc < 2) {
        fprintf (stderr, "Too few arguments\n");
        return 1;
    }

    dir = opendir (argv[1]);
    if (dir == NULL) {
        fprintf (stderr, "opendir() error\n");
        return 1;
    }

    while ((entry = readdir (dir)) != NULL) {
        printf ("%s\t\t", entry->d_name);
    
        if (chdir (argv[1]) == -1) {
            fprintf (stderr, "chdir() error\n");
            return 1;
        }

        print_stat (entry->d_name);
    }
    
    closedir (dir);
    return 0;
}