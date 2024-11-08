#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex_a = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_b = PTHREAD_MUTEX_INITIALIZER;

void *thread_func1(void *arg) {
    printf("Thread 1 tentando bloquear mutex A\n");
    pthread_mutex_lock(&mutex_a);
    sleep(1);
    printf("Thread 1 tentando bloquear mutex B\n");
    pthread_mutex_lock(&mutex_b);

    // Seção crítica
    printf("Thread 1 na seção crítica\n");

    pthread_mutex_unlock(&mutex_b);
    pthread_mutex_unlock(&mutex_a);
    pthread_exit(NULL);
}

void *thread_func2(void *arg) {
    printf("Thread 2 tentando bloquear mutex B\n");
    pthread_mutex_lock(&mutex_b);
    sleep(1);
    printf("Thread 2 tentando bloquear mutex A\n");
    pthread_mutex_lock(&mutex_a);

    // Seção crítica
    printf("Thread 2 na seção crítica\n");

    pthread_mutex_unlock(&mutex_a);
    pthread_mutex_unlock(&mutex_b);
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, thread_func1, NULL);
    pthread_create(&thread2, NULL, thread_func2, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
