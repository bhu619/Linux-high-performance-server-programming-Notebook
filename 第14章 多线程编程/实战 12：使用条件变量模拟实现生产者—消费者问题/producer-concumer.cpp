#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;	/* 初始化互斥锁 */
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;		/* 初始化条件变量 */
int buffer = 0;										/* 产品，代表共享资源 */

/* 生产者线程 */
void* producer(void* arg) {
    pthread_mutex_lock(&mutex);
    buffer = 1; // 生产产品
    printf("Producer: Produced an item\n");
    pthread_cond_signal(&cond); // 通知消费者
    pthread_mutex_unlock(&mutex);
    sleep(rand() % 3); // 随机延时0-2秒
    return NULL;
}

/* 消费者线程 */
void* consumer(void* arg) {
    pthread_mutex_lock(&mutex);
    while (buffer == 0) {
        printf("Consumer: Waiting for item\n");
        pthread_cond_wait(&cond, &mutex); // 等待产品，自动释放互斥锁并使线程进入等待状态
    }
    buffer = 0; // 消费产品
    printf("Consumer: Consumed an item\n");
    pthread_mutex_unlock(&mutex);
    sleep(rand() % 3); // 随机延时0-2秒
    return NULL;
}

int main() {
    srand(time(NULL)); // 初始化随机数生成器
    
    /* 创建线程 */
    pthread_t prod, cons;
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    /* 等待线程结束 */
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    /* 资源释放 */
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}