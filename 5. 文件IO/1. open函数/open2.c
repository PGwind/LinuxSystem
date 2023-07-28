/*************************************************************************
        > File Name: open.c
        > Author: echo
        > Mail: big_fw@foxmail.com
        > Created Time: Fri 28 Jul 2023 10:23:22 AM CST
 ************************************************************************/

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main()
{   
    int fd; 
    fd = open("./dict1.cp", O_RDONLY); 

    printf("fd = %d, errno = %d:%s\n", fd, errno, strerror(errno));
    
    close(fd); // 关闭文件描述符  成功0 失败-1

    return 0;
}
