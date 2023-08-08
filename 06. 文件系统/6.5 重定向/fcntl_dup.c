/*************************************************************************
        > File Name: fcntl_dup.c
        > Author: echo
        > Mail: echobydq@gmail.com
        > Created Time: Sun 30 Jul 2023 05:53:17 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd1 = open(argv[1], O_RDWR);
    
    printf("fd1 = %d\n", fd1);

    int newfd = fcntl(fd1, F_DUPFD, 0); // 0被占用，fcntl使用文件描述符表中可用的最小文件描述符返回
    printf("newfd = %d\n", newfd);

    int newfd2 = fcntl(fd1, F_DUPFD, 7); // 7，未被占用，返回 >= 7 的文件描述符
    printf("newfd2 = %d\n", newfd2);

    int ret = write(newfd2, "YYYYYYY", 7);
    printf("ret = %d\n", ret);

    close(fd1);

    return 0;
}

