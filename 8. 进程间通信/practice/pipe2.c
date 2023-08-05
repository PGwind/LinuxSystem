#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

int main()
{
    int i;
    int fd[2];
    int ret;
    pid_t pid;

    ret = pipe(fd);
    if (ret == -1) {
        sys_err("pipe error");
    }
    
    for (i = 0; i < 2; i++) {
        pid = fork();
        if (pid == -1) {
            sys_err("fork errror");
        }
        // 子进程是一个独立的进程，它会继续执行从 fork() 调用后的代码
        // 也就是说，break后子进程执行下面的if语句，父进程则继续循环到结束
        if (pid == 0)
            break;
    }

    if (i == 2) {
        for (int j = 0; j < 2; j++) {
            close(fd[j]);
            wait(NULL);
        }
    } else if (i == 0) {    // 兄进程
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        execlp("ls", "ls", NULL);
        sys_err("execlp ls error");
    } else if (i == 1) {    // 弟进程
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        execlp("wc", "wc", "-l", NULL);
        sys_err("execlp wc error");
    }
    
    return 0;
}
