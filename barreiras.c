#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 5
#define NUM_BARRIERS 3

pthread_barrier_t barrier;

void *thread_task(void *arg) {
    int id = *(int *)arg;

    for (int i = 0; i < NUM_BARRIERS; i++) {
        printf("Thread %d antes da barreira %d\n", id, i + 1);
        sleep(rand() % 3);

        // Ponto de sincronização
        pthread_barrier_wait(&barrier);

        printf("Thread %d apos a barreira %d\n", id, i + 1);
        sleep(rand() % 2);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Inicialização da barreira
    pthread_barrier_init(&barrier, NULL, NUM_THREADS);

    // Criação das threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, thread_task, &thread_ids[i]);
    }

    // Junção das threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destruição da barreira
    pthread_barrier_destroy(&barrier);

    return 0;
}
