#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

int main()
{
    printf("-------exec test\n");

    return 0;
}
