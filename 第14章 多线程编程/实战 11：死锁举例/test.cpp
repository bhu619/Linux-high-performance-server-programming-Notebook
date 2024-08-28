#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

int a = 0;
int b = 0;
pthread_mutex_t mutex_a;
pthread_mutex_t mutex_b;

void *another (void *arg) {
    pthread_mutex_lock(&mutex_b);	/* 子线程上锁 mutex_b */
    printf("in child thread, got mutex b, waiting for mutex a\n");
    sleep(5);
    ++b;
    pthread_mutex_lock(&mutex_a);	/* 子线程上锁 mutex_a */
    b += a++;
    
    pthread_mutex_unlock(&mutex_a);	/* 解锁 */
    pthread_mutex_unlock(&mutex_b);
    pthread_exit(NULL);
}

int main () {
    pthread_t id;

    pthread_mutex_init(&mutex_a, NULL);	/* 初始化互斥锁 */
    pthread_mutex_init(&mutex_b, NULL);
    pthread_create(&id, NULL, another, NULL);	/* 创建线程 */

    pthread_mutex_lock(&mutex_a);	/* 主线程上锁 mutex_a */
    printf("in parent thread, got mutex a, waiting for mutex b\n");
    sleep(5);
    ++a;
    
    pthread_mutex_lock(&mutex_b);	/* 主线程上锁 mutex_b */
    a += b++;
    
    pthread_mutex_unlock(&mutex_b);
    pthread_mutex_unlock(&mutex_a);

    /* 主线程等待子线程结束，然后销毁互斥锁以释放资源 */
    pthread_join(id, NULL);
    pthread_mutex_destroy(&mutex_a);
    pthread_mutex_destroy(&mutex_b);

    return 0;
}