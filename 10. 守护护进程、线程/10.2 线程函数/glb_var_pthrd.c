#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <pthread.h>

int var = 100;

void *tfn(void *arg)
{
    var = 200;
    printf("thread, var = %d\n", var);

    return NULL;
}

int main()
{
    printf("At first var = %d\n", var);

    pthread_t tid;
    pthread_create(&tid, NULL, tfn, NULL);
    sleep(1);

    printf("after pthread_create, var = %d\n", var);

    return 0;
}
