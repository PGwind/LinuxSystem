#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <signal.h>


int i = 0;
void handler(int signum) {
    printf("%d\n", i ++);
}

int main()
{
    struct itimerval timer;

    // 初始化定时器
    timer.it_value.tv_sec = 1;  // 初始定时器时间为1秒
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 1;   //  重复定时器时间为1秒
    timer.it_interval.tv_usec = 0;

    // B
    // 设置信号处理函数
    signal(SIGALRM, handler);

    // 启动定时器
    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("setitimer error");
        exit(1);
    }

    while (1);

    return 0;
}
