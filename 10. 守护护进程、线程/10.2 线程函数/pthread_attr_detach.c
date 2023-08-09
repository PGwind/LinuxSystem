#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <pthread.h>
#include <string.h>

void *tfn(void *arg)
{
    printf("thread: pid = %d, tid = %lu\n", getpid(), pthread_self());

    return NULL;
}

int main()
{
    pthread_t tid;
    pthread_attr_t attr;    // 创建一个线程属性结构体变量

    int ret = pthread_attr_init(&attr); // 初始化线程属性
    if (ret != 0) {
        fprintf(stderr, "pthread_attr_init error: %s\n", strerror(ret));
        exit(1);
    }

    ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);  // 设置线程属性为 分离属性
    if (ret != 0) {
        fprintf(stderr, "pthread_attr_setdetachstate error: %s\n", strerror(ret));
        exit(1);
    }
    
    ret = pthread_create(&tid, &attr, tfn, NULL);   // 借助修改后的线程属性创建为分离态的新线程
    if (ret != 0) {
        fprintf(stderr, "pthread_create error: %s\n", strerror(ret));
        exit(1);
    }

    ret = pthread_attr_destroy(&attr);  // 销毁线程属性
    if (ret != 0) {
        fprintf(stderr, "pthread_attr_destroy error: %s\n", strerror(ret));
        exit(1);
    }
    
    sleep(1);   // 等待

    ret = pthread_join(tid, NULL);
    if (ret != 0) {
        fprintf(stderr, "pthread_join error: %s\n", strerror(ret));
        exit(1);
    }

    printf("main: pid = %d, tid = %lu\n", getpid(), pthread_self());

    pthread_exit((void *)0);
}
