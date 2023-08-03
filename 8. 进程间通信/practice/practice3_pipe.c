#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

int main()
{
    int ret, i, bytesRead;
    int fd[2];
    char buf[1024];
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

    // 两个子进程写，父进程读
    if (i == 0) {    
        close(fd[0]);
        write(fd[1], "1.hello\n", strlen("1.hello\n"));
    } else if (i == 1) {    
        close(fd[0]);
        sleep(1);
        write(fd[1], "2.world\n", strlen("2.world\n"));
    } else {
        close(fd[1]);
        sleep(2);
        bytesRead = read(fd[0], buf, 1024);
        write(STDOUT_FILENO, buf, bytesRead);

        for (i = 0; i < 2; i++) {
            wait(NULL);
        }
    }
    
    return 0;
}
