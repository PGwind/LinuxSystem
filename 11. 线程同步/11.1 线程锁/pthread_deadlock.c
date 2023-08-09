#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutexA = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexB = PTHREAD_MUTEX_INITIALIZER;

void *threadA(void *arg) {
    pthread_mutex_lock(&mutexA);
    printf("Thread A acquired mutex A\n");
    
    // Sleep to simulate some work
    sleep(1);
    
    printf("Thread A trying to acquire mutex B...\n");
    pthread_mutex_lock(&mutexB);
    printf("Thread A acquired mutex B\n");
    
    pthread_mutex_unlock(&mutexB);
    pthread_mutex_unlock(&mutexA);
    
    return NULL;
}

void *threadB(void *arg) {
    pthread_mutex_lock(&mutexB);
    printf("Thread B acquired mutex B\n");
    
    // Sleep to simulate some work
    sleep(1);
    
    printf("Thread B trying to acquire mutex A...\n");
    pthread_mutex_lock(&mutexA);
    printf("Thread B acquired mutex A\n");
    
    pthread_mutex_unlock(&mutexA);
    pthread_mutex_unlock(&mutexB);
    
    return NULL;
}

int main() {
    pthread_t tidA, tidB;
    
    pthread_create(&tidA, NULL, threadA, NULL);
    pthread_create(&tidB, NULL, threadB, NULL);
    
    pthread_join(tidA, NULL);
    pthread_join(tidB, NULL);
    
    return 0;
}

