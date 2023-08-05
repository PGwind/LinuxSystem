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
        sys_err("fork errror");
    } else if (pid > 0) {
        close(fd[1]);           // 关闭 写
        dup2(fd[0], STDIN_FILENO);
        execlp("wc", "wc", "-l", NULL);
        sys_err("execlp errror");
    } else if (pid == 0) {
        close(fd[0]);           // 关闭 读
        dup2(fd[1], STDOUT_FILENO);
        execlp("ls", "ls", NULL);
        sys_err("execlp errror");
    }

    return 0;
}
