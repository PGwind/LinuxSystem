#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
int main()
{
    pid_t pid = fork();

    if (pid > 0) {
        while(1) {
            printf("parent = %d\n", getpid());
            sleep(1);
        }
    } else if (pid == 0) {
            printf("child = %d ppid = %d\n", getpid(), getppid());
            sleep(10);
            kill(0, SIGKILL);
    } else {
        perror("fork error");
        exit(1);
    }

    return 0;

}
