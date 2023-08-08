/*************************************************************************
        > File Name: unlink.c
        > Author: echo
        > Mail: echobydq@gmail.com
        > Created Time: Sat 29 Jul 2023 06:27:48 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
    int fd;
    int ret;
    char *p = "test of unlink\n";
    char *p2 = "after write something.\n";

    fd = open("temp.txt", O_RDWR | O_CREAT | O_TRUNC, 0644); // 临时文件，程序结束销毁
    if (fd < 0) {
        perror("open temp error");
        exit(1);
    }

    ret = unlink("temp.txt"); // 具备释放条件
    if (ret < 0) {
        perror("unlink error");
        exit(1);
    }

    ret = write(fd, p, strlen(p));
    if (ret == -1) {
        perror("--------write error");
    }

    printf("hi! I'm printf\n");
    ret = write(fd, p2, strlen(p2));
    if (ret == -1) {
        perror("--------write error");
    }
    
    p[3] = 'H';  // 发送段错误，无法消除临时文件

    printf("Enter anykey continue\n");
    getchar();

    close(fd);

    /*
    ret = unlink("temp.txt"); // 具备释放条件
    if (ret < 0) {
        perror("unlink error");
        exit(1);
    }
    */

    return 0;
}   
