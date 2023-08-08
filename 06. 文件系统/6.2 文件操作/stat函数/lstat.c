/*************************************************************************
        > File Name: stat.c
        > Author: echo
        > Mail: echobydq@gmail.com
        > Created Time: Sat 29 Jul 2023 03:53:46 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    struct stat sbuf;

    int ret = lstat(argv[1], &sbuf);
    if (ret == -1) {
        perror("stat error");
        exit(1);
    }

    if (S_ISREG(sbuf.st_mode)) {
        printf("It's a regular\n");
    } else if (S_ISDIR(sbuf.st_mode)) {
        printf("It's a dir\n");
    } else if (S_ISFIFO(sbuf.st_mode)) {
        printf("It's a pipe\n");
    } else if (S_ISLNK(sbuf.st_mode)) {
        printf("It's a soft link\n");
    } 

    return 0;
}
