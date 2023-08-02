#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int i;
    pid_t pid, wpid, tmpid;

    for (i = 0; i < 5; i ++) {
        pid = fork();
        if (pid == 0) {
            break;
        }
        if (i == 2) {
            tmpid = pid;
            printf("---------pid = %d\n", tmpid);
        }
    }

    if (i == 5) {
        // sleep(5);
        // wait(NULL);                          // 一次 wait/waitpid 函数调用，只能回首一个子进程
        // wpid = waitpid(-1, NULL, WNOHANG);   // 回收任意子进程，没有结束的子进程、父进程直接返回0
        printf("------- in parent, before waitpid, pid = %d\n", tmpid);
        // wpid = waitpid(tmpid, NULL, WNOHANG);     // 指定一个进程回收, 不阻塞
         wpid = waitpid(tmpid, NULL, 0);     // 指定一个进程回收，阻塞回收
        
        if (wpid == -1) {
            perror("waitpid error");
            exit(1);
        }
        printf("I'm parent, wait a child finish: %d\n", wpid);
    }
    else {
        sleep(i);
        printf("I'm %dth child, pid = %d\n", i+1, getpid());
    }

    return 0;
}
