#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(void) 
{
    char buf[1024];
    char *str = "---------- test2 write success --------\n";
    int bytesRead;

    sleep(2);   // 睡眠2秒，等待 test_w 将数据写入test.txt

    int fd = open("test.txt", O_RDWR);

    bytesRead = read(fd, buf, sizeof(buf));

    write(STDOUT_FILENO, buf, bytesRead);

    write(fd, str, strlen(str));

    printf("test2 read/write finish\n");

    close(fd);

    return 0;
}
