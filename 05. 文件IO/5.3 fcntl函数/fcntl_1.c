/*************************************************************************
        > File Name: fcntl_1.c
        > Author: echo
        > Mail: echobydq@gmail.com
        > Created Time: Fri 28 Jul 2023 08:02:55 PM CST
 ************************************************************************/

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd = open("example.txt", O_RDONLY);  // 打开文件 example.txt，只读模式

    // 获取文件状态标志
    int flags = fcntl(fd, F_GETFL);
    if (flags == -1) {
        perror("fcntl");
        return 1;
    }

    printf("File flags before modification: %d\n", flags);

    // 添加 O_APPEND 标志
    flags |= O_APPEND;
    
    // 设置文件状态标志
    int result = fcntl(fd, F_SETFL, flags);
    if (result == -1) {
        perror("fcntl");
        return 1;
    }

    printf("File flags after modification: %d\n", flags);

    close(fd);
    return 0;
}
