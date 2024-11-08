#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 5
#define MAX_CONCURRENT_THREADS 2

sem_t semaphore;

void *thread_task(void *arg) {
    int id = *(int *)arg;

    // Aguardar pelo semáforo
    sem_wait(&semaphore);

    // Seção crítica
    printf("Thread %d entrando na seção crítica.\n", id);
    sleep(rand() % 3 + 1);
    printf("Thread %d saindo da seção crítica.\n", id);

    // Sinalizar o semáforo
    sem_post(&semaphore);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Inicialização do semáforo
    sem_init(&semaphore, 0, MAX_CONCURRENT_THREADS);

    // Criação das threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, thread_task, &thread_ids[i]);
    }

    // Junção das threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destruição do semáforo
    sem_destroy(&semaphore);

    return 0;
}
