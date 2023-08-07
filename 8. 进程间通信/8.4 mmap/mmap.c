#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

int main()
{
    char *p = NULL;
    int fd;

    fd = open("testmap", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        sys_err("open error");

    /*
    lseek(fd, 10, SEEK_END);
    write(fd, "\0", 1);
    */
    int st = unlink("testmap");
    if (st == -1) {
        perror("unlink error");
        exit(1);
    }

    ftruncate(fd, 20); // 拓展文件
    int len = lseek(fd, 0, SEEK_END);

    p = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (p == MAP_FAILED) {
        sys_err("mmap error");
    }
    close(fd);

    // 使用 p 对文件进行读写操作
    strcpy(p, "hello mmap");
    
    printf("—————— %s\n", p);

    int ret = munmap(p, len);
    if (ret == -1) {
        sys_err("munmap error");
    }
    
    return 0;
}
