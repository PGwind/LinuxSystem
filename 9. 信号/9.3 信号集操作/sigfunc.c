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

void print_set(sigset_t *set)
{
    int i;
    for (i = 1; i < 32; i++){
         if (sigismember(set, i))
             putchar('1');
         else 
             putchar('0');
    }
    printf("\n");
}

int main()
{
    sigset_t set, oldset, pedset;
    int ret1 = 0, ret2 = 0;

    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGQUIT);
    sigaddset(&set, SIGBUS);
    sigaddset(&set, SIGKILL);

    ret1 = sigprocmask(SIG_BLOCK, &set, &oldset);
    if (ret1 == -1)
        sys_err("sigprocmask error");

    while (1) {
        ret2 = sigpending(&pedset);
        if (ret2 == -1)
            sys_err("sigpending error");
        print_set(&pedset);
        sleep(1);
    }

    return 0;
}
