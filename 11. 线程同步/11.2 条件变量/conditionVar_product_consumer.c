/*
 * 借助条件变量模拟 生产者-消费者 问题
 * 简略了函数返回值检测、打印错误信息
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <pthread.h>
#include <string.h>

/* 打印错误信息 */
void err_thread(int ret, char *str)

{
    if (ret != 0) {
        fprintf(stderr, "%s:%s\n", str, strerror(ret));
        pthread_exit(NULL);
    }
}

/* 链表作为共享数据，需要被互斥量保护 */
struct msg {
    struct msg *next;
    int num;
};

struct msg *head;

/* 静态初始化 */
pthread_cond_t has_product = PTHREAD_COND_INITIALIZER;  // 条件变量(是否有产品)
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;       // 互斥量

void *producer(void *p) // 生产者
{
    struct msg *mp;

    for (;;) {
        mp = malloc(sizeof(struct msg));
        mp->num = rand() % 1000 + 1;        // 模拟生产一个产品
        printf("-Produce %lu---%d\n",pthread_self(), mp->num);

        pthread_mutex_lock(&lock);      // 加锁 写入数据(头插法)
        mp->next = head;
        head = mp;
        pthread_mutex_unlock(&lock);    // 解锁

        pthread_cond_signal(&has_product);  //  将等待在条件变量上的一个线程唤醒（生产完唤醒消费者）
        
        sleep(rand() % 5);
    }
}

void *consumer(void *p) // 消费者
{
    struct msg *mp;

    for (;;) {
        pthread_mutex_lock(&lock);      // 加锁 读取数据
        while (head == NULL) {                      // 头指针为空，说明没有节点，即没有产品
            pthread_cond_wait(&has_product, &lock); // 阻塞、解锁，等待生产者制作完毕发送唤醒信号后 重新加锁
        }
        mp = head;
        head = mp->next;                            //  模拟消费掉一个产品
        pthread_mutex_unlock(&lock);    // 解锁

        printf("-Consume %lu---%d\n", pthread_self(), mp->num);
        free(mp);
        sleep(rand() % 5);
    }
}


int main()
{
    int ret; // 返回值
    pthread_t pid, cid;
    srand(time(NULL));

    ret = pthread_create(&pid, NULL, producer, NULL);   // 生产者
    if (ret != 0)
        err_thread(ret, "pthread_create producer error");
    
    pthread_create(&cid, NULL, consumer, NULL); // 消费者
    if (ret != 0)
        err_thread(ret, "pthread_create consumer error");
    
    pthread_join(pid, NULL);
    pthread_join(cid, NULL);

    return 0;
}
