#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void sys_err(char *str)
{
    perror(str);
    exit(-1);
}

int main(int argc, char *argv[])
{
    int fd, i;
    char buf[4096];

    if (argc < 2) {
        printf("Enter like this：./a.out fifoname\n");
        return -1;
    }

    fd = open(argv[1], O_WRONLY);
    if (fd < 0)
        sys_err("open error");

    i = 0;
    while (1) {
        sprintf(buf, "hello echo %d\n", i++);

        write(fd, buf, strlen(buf));
        sleep(1);
    }
    close(fd);

    return 0;
}
