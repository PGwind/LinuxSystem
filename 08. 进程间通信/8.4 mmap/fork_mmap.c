#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>

int var = 100;

int main(void)
{
    int *p;
    pid_t pid;

    int fd;
   
    // MAP_ANON  匿名映射区，不需要创建文件
    /*
    fd = open("temp", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open error");
        exit(1);
    }
    int ret = unlink("temp");     // 删除临时文件目录项，使之具备被释放的条件
    if (ret == -1) {
        perror("unlink error");
        exit(1);
    }
    ftruncate(fd, 4);
    */

    p = (int *)mmap(NULL, 40, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
    // p = (int *)mmap(NULL, 4, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (p == MAP_FAILED) {
        perror("mmap error");
        exit(1);
    }
    // close(fd);          // 映射区建立完毕，即可关闭文件

    pid = fork();
    if (pid == 0) { // 子进程
        *p = 7000;  // 写共享内存
        var = 1000;
        printf("child, *p = %d, var = %d\n", *p, var);
    } else if (pid > 0) {
        sleep(1);
        // 读时共享，写时复制， var = 100
        printf("parent, *p = %d, var = %d\n", *p, var);
        wait(NULL);

        int ret = munmap(p, 4);
        if (ret == -1) {
            perror("munmap error");
            exit(1);
        }
    } else {
        perror("fork error");
        exit(1);
    }

    return 0;
}
