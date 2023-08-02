#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    pid_t pid1, pid2, pid3;
    int status;
    
    /* 
    int fd;
    fd = open("work_waitpid.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open error");
        exit(1);
    }

    // PS：部分信息子进程打印信息不会输出到文件
    dup2(fd, STDOUT_FILENO); // 将终端输出到文件 word_waitpid.txt
    */

    // 进程1
    pid1 = fork();
    if (pid1 == 0) {
        // 执行 ls 命令
        printf("Child 1: PID = %d, Parent PID = %d\n",getpid(), getppid());
        execlp("ls", "ls", "-l", NULL);
        perror("execlp error");
        exit(1);
    } else if (pid1 == -1) {
        perror("pid1 fork error");
        exit(1);
    }
    
    // 进程2
    pid2 = fork();
    if (pid2 == 0) {
        // 自定义程序1
        printf("Child 2: PID = %d, Parent PID = %d\n",getpid(), getppid());
        exit(0);
    } else if (pid2 == -1) {
        perror("pid2 fork error");
        exit(1);
    }

    // 进程3
    pid3 = fork();
    if (pid3 == 0) {
        // 自定义程序3
        printf("Child 3: PID = %d, Parent PID = %d\n",getpid(), getppid());
        // 段错误
        int *p = NULL;
        *p = 123;
        exit(0);
    } else if (pid3 == -1) {
        perror("pid2 fork error");
        exit(1);
    }
    
    // 父进程调用 waitpid() 对子进程进行回收
    for (int i = 0; i < 3; i++) {
        pid_t child_pid = waitpid(-1, &status, 0); // 采用阻塞方式回收任意进程
        if (child_pid > 0) {
            if (WIFEXITED(status)) {
                printf("Child process %d exited with status %d\n", child_pid, WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                printf("Child process %d terminated by signal %d\n", child_pid, WTERMSIG(status));
            }
        }else {
                perror("waitpid error");
                exit(1);
            }
        }
    printf("Parent process: PID = %d\n", getpid());

    return 0;
}

