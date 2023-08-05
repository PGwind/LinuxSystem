#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

int main()
{
    int fd[2];
    int ret;
    pid_t pid;

    ret = pipe(fd);
    if (ret == -1) {
        sys_err("pipe error");
    }

    pid = fork();
    if (pid == -1) {
        sys_err("fork error");
    } else if (pid > 0) {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        execlp("grep", "grep", "-E", "^[0-9]{5,}", NULL);
        sys_err("execlp error");
    } else if (pid == 0) {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        execlp("ps", "ps", "-e", NULL);
        sys_err("execlp error");
    }

    return 0;
}

