#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

int main()
{
    int ret = mkfifo("myfifo1", 0644);
    if (ret == -1)
        sys_err("mkfifo  error");

    return 0;
}
