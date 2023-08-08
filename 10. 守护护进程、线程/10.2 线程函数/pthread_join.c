#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <pthread.h>
#include <string.h>

typedef struct thrd {
    int var;
    char str[20];
} Thrd;

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

/*
void *tfn(void *arg)
{
    Thrd tval;      //  局部变量地址，不可做返回值

    tval.var = 100;
    strcpy(tval.str, "hello thread");

    return (void *)&tval;
}
*/

/*
void *tfn(void *arg)  // 方法1
{
    Thrd *tval;

    tval = malloc(sizeof(Thrd));

    tval->var = 100;
    strcpy(tval->str, "hello thread");

    return (void *)tval;
}
*/

void *tfn(void *arg)
{
    Thrd *tval = (Thrd *)arg;

    tval->var = 100;
    strcpy(tval->str, "hello thread");

    return (void *)tval;
}


int main()
{
    pthread_t tid;

    struct thrd *retval;
    struct thrd arg;

    //int ret = pthread_create(&tid, NULL, tfn, NULL); // 对应方法1
    int ret = pthread_create(&tid, NULL, tfn, (void *)&arg); 
    if (ret != 0)
        sys_err("pthread_create error");
    
    ret = pthread_join(tid, (void **)&retval);
    if (ret != 0) {
        sys_err("pthread_join error");
    }

    printf("child thread exit with var = %d, str = %s\n", retval->var, retval->str);

    pthread_exit(NULL);

}
