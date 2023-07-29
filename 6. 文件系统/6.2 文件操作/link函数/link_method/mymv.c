/*************************************************************************
        > File Name: link.c
        > Author: echo
        > Mail: echobydq@gmail.com
        > Created Time: Sat 29 Jul 2023 06:11:47 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    link(argv[1], argv[2]);

    unlink(argv[1]);

    return 0;
}
