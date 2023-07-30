#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char *argv[]) 
{
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // 复制文件描述符
    int new_fd = dup(fd);

    printf("Original file descriptor: %d\n", fd);
    printf("New file descriptor: %d\n", new_fd);

    close(fd); // 注意：关闭原文件描述符不会影响新的文件描述符

    // 使用新的文件描述符读取文件内容
    char buffer[10];
    ssize_t bytes_read = read(new_fd, buffer, sizeof(buffer) - 1);
    buffer[bytes_read] = '\0';
    printf("Content: %s\n", buffer);

    close(new_fd);
    return 0;
}
