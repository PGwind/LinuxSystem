#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

int main(int argc, char *argv[])
{
    int ret;
    ssize_t bytesRead;
    int fd[2];
    pid_t pid;

    char *str = "Hello Pipe\n";
    char buf[1024];

    ret = pipe(fd);
    if (ret == -1) 
        sys_err("pipe error");
    
    pid = fork ();
    
    if (pid > 0) {
        close(fd[0]);          // 父进程关闭 读
        write(fd[1], str, strlen(str));
        sleep(3);
        close(fd[1]);
    } else if (pid == 0) {
        close(fd[1]);          // 子进程关闭 写
        bytesRead = read(fd[0], buf, sizeof(buf)); // read返回实际读取的字节数
        printf("child read bytesRead = %ld\n", bytesRead);
        write(STDOUT_FILENO, buf, bytesRead);
        close(fd[0]);
    } else {
        perror("fork error");
        exit(1);
    }

    return 0;

}
