#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int i;
    pid_t pid, wpid;

    for (i = 0; i < 5; i ++) {
        pid = fork();
        if (pid == 0) {
            break;
        }
    }

    if (i == 5) {
        /*
        while ((wpid = waitpid(-1, NULL, 0))) {     使用阻塞方式回收子进程
            printf("wait child %d\n", wpid);
        }
        */
        while ((wpid = waitpid(-1, NULL, WNOHANG)) != -1) {     // 使用非阻塞方式回收子进程
            if (wpid > 0) {
                printf("wait child %d\n", wpid);
            } else if (wpid == 0) {
                sleep(1);
                continue;
            }
        }
   }
    else {
        sleep(i);
        printf("I'm %dth child, pid = %d\n", i+1, getpid());
    }

    return 0;
}
