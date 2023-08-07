#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

int main(void)
{
    int fd1, fd2;
    pid_t pid;
    char buf[1024];
    char *str = "---------------- test for shared fd in parent child process ---------\n";

    pid = fork();
    if (pid < 0) {
        perror("fork error");
        exit(1);
    } else if (pid == 0) {
        fd1 = open("test.txt", O_RDWR | O_TRUNC | O_CREAT, 0644);
        if (fd1 < 0) {
            perror("open error");
            exit(1);
        }
        sleep(1);
        write(fd1, str, strlen(str));
        printf("child wrote over...\n");
    } else {
        fd2 = open("test.txt", O_RDWR);
        if (fd2 < 0) {
            perror("open error");
            exit(1);
        }
        //sleep(1);

        int len = read(fd2, buf, sizeof(buf));
        printf("------- parent read len = %d\n", len);
        write(STDOUT_FILENO, buf, len);
        printf("------- parent write len = %d\n", len);

        wait(NULL);
    }

    return 0;
}
