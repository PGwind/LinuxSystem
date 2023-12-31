/*************************************************************************
        > File Name: lseek.c
        > Author: echo
        > Mail: echobydq@gmail.com
        > Created Time: Sat 29 Jul 2023 11:57:11 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main()
{
    int fd, n;
    char msg[] = "It's a test for lseek\n";
    char ch;

    fd = open("test1.txt", O_RDWR | O_CREAT, 0644);
    if (fd < 0) {
        perror("open lseek.txt error");
        exit(1);
    }

    write(fd, msg, strlen(msg)); // 使用fd对打开的文件进行写操作，读写位置位于文件结尾处
    
    lseek(fd, 0, SEEK_SET);   // 修改文件读写位置，位于文件开头
    
    while ((n = read(fd, &ch, 1))) {
        if (n < 0) {
            perror("read error");
            exit(1);
        }
        write(STDOUT_FILENO, &ch, n); // 将文件内容按字节读出，写出到屏幕
    }

    close(fd);

    return 0;
}
