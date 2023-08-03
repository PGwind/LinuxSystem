#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <pthread.h>

int main()
{
    int i;
    pid_t pid;
    for (i = 0; i < 5; i ++) {
        pid = fork();     // 循环期间，子进程不fork
        
        // 子进程是一个独立的进程，它会继续执行从 fork() 调用后的代码
        // 也就是说，break后子进程执行下面的if语句，父进程则继续循环到结束            
        if (pid == 0)
            break;
    }
    if (i == 5) {         // 父进程，从表达式2跳出
        sleep(5);
        printf("I'm parent\n");
    }
    else {
        sleep(i);         // 子进程，从 break 跳出
        printf("I'm %dth child\n", i+1);
    }

    return 0;
}