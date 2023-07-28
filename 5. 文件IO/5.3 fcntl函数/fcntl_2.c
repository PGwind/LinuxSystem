/*************************************************************************
        > File Name: fcntl.c
        > Author: echo
        > Mail: echobydq@gmail.com
        > Created Time: Fri 28 Jul 2023 07:48:19 PM CST
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define MSG_TRY "try again\n"

int main(void)
{
    char buf[10];
    int flags, n;

    flags = fcntl(STDIN_FILENO, F_GETFL); // 获取 stdin 属性信息

    if (flags == -1) {
        perror("fcntl error");
        exit(1);
    }

    flags |= O_NONBLOCK; // 添加上非阻塞状态
    int ret = fcntl(STDIN_FILENO, F_SETFL, flags);

    if (ret == -1) {
        perror("fcntl error");
        exit(1);
    }

tryagain:
    n = read(STDIN_FILENO, buf, 10);

    if (n < 0) {
        if (errno != EAGAIN) {
            perror("read /dev/tty");
            exit(1);
        }
        sleep(3);
        write(STDOUT_FILENO, MSG_TRY, strlen(MSG_TRY));
        goto tryagain;
    }
    
    write(STDOUT_FILENO, buf, n);

    return 0;
}

