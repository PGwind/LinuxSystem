#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <pthread.h>

int main()
{
    printf("before fork-1-\n");
    printf("before fork-2-\n");
    printf("before fork-3-\n");
    printf("before fork-4-\n");

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork error");
        exit(1);
    } else if (pid == 0) {
        printf("---child is created\n");
    } else if (pid > 0) {
        printf("---parent process：mychild is %d\n", pid);
    }
    
    printf("========================= end of file\n");

    return 0;
}
