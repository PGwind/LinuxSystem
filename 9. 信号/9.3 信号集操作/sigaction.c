#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

void sig_catch(int signum)      // 回调函数
{
    if (signum == SIGINT) {
        printf("catch %d\n", signum);
        sleep(5);
    } 
    /* else if (signum == SIGQUIT) {
        printf("------ catch %d\n", signum);
    } */
    return;
}

int main()
{
    struct sigaction act, oldact;
    
    act.sa_handler = sig_catch;     // 设置回调函数
    sigemptyset(&(act.sa_mask));    // 清空屏蔽字(仅在捕捉函数执行期间生效)
    sigaddset(&act.sa_mask, SIGQUIT);
    act.sa_flags = 0;                // 设置默认属性

    int ret = sigaction(SIGINT, &act, &oldact); // 注册信号捕捉函数
    if (ret == -1)
        sys_err("sigaction error");

    // ret = sigaction(SIGQUIT, &act, &oldact);
    
    while (1);

    return 0;
}
