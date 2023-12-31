#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int status;
    pid_t pid, wpid;

    pid = fork();

    if (pid == 0) {
        printf("---child, my pid = %d, going to sleep 3s\n", getpid());
        sleep(15);
        printf("---------------- child die ---------------\n");
        return 73;
    } else if (pid > 0) {
        // wpid = wait(NULL);           // 不关心子进程结束原因
        wpid = wait(&status);        // 如果子进程未终止，父进程阻塞在这个函数上
        if (wpid == -1) {
            perror("wait error");
            exit(1);
        }
        if (WIFEXITED(status)) {            // 为真，说明子进程正常终止
            printf("child exit with %d\n", WEXITSTATUS(status));
        }
        if (WIFSIGNALED(status)) {          // 为真，说明子进程是被信号终止
            printf("child kill with signal %d\n", WTERMSIG(status));
        }
        printf("------------ parent wait finish: %d\n", wpid);
    } else {
        perror("fork");
        return 1;
    }

    return 0;
}
