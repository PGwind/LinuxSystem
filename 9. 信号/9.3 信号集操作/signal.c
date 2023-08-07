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

void sig_catch(int signum)
{
    printf("catch %d\n", signum);
    return;
}

int main()
{
    signal(SIGINT, sig_catch);


    while (1);

    return 0;
}
