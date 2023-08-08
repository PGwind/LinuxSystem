/*************************************************************************
        > File Name: mycat.c
        > Author: echo
        > Mail: echobydq@gmail.com
        > Created Time: Sun 30 Jul 2023 05:32:22 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd1, fd2;
    int fdret, ret;

    fd1 = open(argv[1], O_RDWR);
    fd2 = open(argv[2], O_RDWR);

    fdret = dup2(fd1, fd2);  // 返回 新文件描述符fd2
    printf("fdret = %d\n", fdret);

    ret = write(fd2, "1234567", 7); // 写入 fd1 指向的文件
    printf("ret = %d\n", ret);

    dup2(fd1,STDOUT_FILENO); // 将屏幕输入，重定向给 fd1 所指向的文件

    printf("-----------------------886");

    close(fd1);
    close(fd2);

    return 0;
}
