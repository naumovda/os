#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int daemon_proc();

int main(){
    daemon_proc();
    sleep(10);

    return 0;
}


int daemon_proc(){
    // become background process
    switch (fork()){
    case -1: return -1;
    case 0: break;  /* child process continues */
    default: _exit(0);  /* parent process exits */
    }

    // start new session with calling process as leader
    if (setsid() == -1)
        return -1;

    // create new process which is not session leader
    switch (fork()){
    case -1: return -1;
    case 0: break;
    default: _exit(0);
    }

    umask(0);  /* clear file creation mask */
    chdir("/");  /* set root directory as cwd */

    // close all file descriptors
    int maxfd = sysconf(_SC_OPEN_MAX);
    for (int fd = 0; fd < maxfd; fd++)
        close(fd);

    // reopen standard file descriptors to dev/null
    close(STDIN_FILENO);
    int fd = open("/dev/null", O_RDWR);

    if (fd != STDIN_FILENO)
        return -1;

    if (dup2(STDIN_FILENO, STDOUT_FILENO) != STDOUT_FILENO)
        return -1;

    if (dup2(STDIN_FILENO, STDERR_FILENO) != STDERR_FILENO)
        return -1;

    return 0;
}
