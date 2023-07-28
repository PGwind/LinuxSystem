/*************************************************************************
        > File Name: open.c
        > Author: echo
        > Mail: big_fw@foxmail.com
        > Created Time: Fri 28 Jul 2023 10:23:22 AM CST
 ************************************************************************/

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{   
    int fd; 
    fd = open("./dict.cp", O_RDONLY | O_CREAT | O_TRUNC, 0644); // 644 rw-r--r--

    printf("fd = %d\n", fd);
    
    close(fd); // 关闭文件描述符  成功0 失败-1

    return 0;
}
