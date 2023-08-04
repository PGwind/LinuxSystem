#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define N 5

int main(void) 
{
    char buf[1024];
    char *str = "---------- 1.success --------\n";
    int bytesRead;

    int fd = open("test.txt", O_RDWR | O_TRUNC | O_CREAT, 0644);

    write(fd, str, strlen(str));
    printf("test1 write into test.txt finish\n");

    sleep(N);

    lseek(fd, 0, SEEK_SET);
    bytesRead = read(fd, buf, sizeof(buf));
    bytesRead = write(STDOUT_FILENO, buf, bytesRead);

    if (bytesRead == -1) {
        perror("write second error");
        exit(1);
    }

    close(fd);

    return 0;
}
