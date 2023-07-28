/*************************************************************************
        > File Name: mycp.c
        > Author: echo
        > Mail: echobydq@gmail.com
        > Created Time: Fri 28 Jul 2023 12:34:19 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define N 1024

int main(int argc, char *argv[])
{
    int fd, fd_out;
    int n;
    char buf[N];

    fd = open("test.txt", O_RDONLY); // read
    if (fd < 0) {
        perror("open test.txt error");
        exit(1);
    }

    fd_out = open("test.cp", O_WRONLY | O_CREAT | O_TRUNC, 0664); // rw-rw--r
    if (fd_out < 0) {
        perror("open test.cp error");
        exit(1);
    }

    // read 返回为读取到的字节数
    while ((n = read(fd, buf, N))) { // 0：读到文件结尾结束循环
        if (n < 0) {
            perror("read error");
            break;
        }
        write(fd_out, buf, n);
    }

    close(fd);
    close(fd_out);

    return 0;
}

