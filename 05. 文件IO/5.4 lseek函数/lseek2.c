/*************************************************************************
        > File Name: lseek2.c
        > Author: echo
        > Mail: echobydq@gmail.com
        > Created Time: Sat 29 Jul 2023 12:22:04 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        perror("open error");
        exit(1);
    }

    int lenth = lseek(fd, 0, SEEK_END);
    printf("file size: %d\n", lenth);

    close(fd);

    return 0;
}

