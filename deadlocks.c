#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Inicialização dos mutexes
pthread_mutex_t mutex_a = PTHREAD_MUTEX_INITIALIZER;  
pthread_mutex_t mutex_b = PTHREAD_MUTEX_INITIALIZER;

// Função que será executada pela Thread 1
void *thread_func1(void *arg) {
    printf("Thread 1 tentando bloquear mutex A\n");
    // Thread 1 tenta bloquear o mutex A
    pthread_mutex_lock(&mutex_a);
    sleep(1);

    printf("Thread 1 tentando bloquear mutex B\n");
    // Thread 1 tenta bloquear o mutex B
    pthread_mutex_lock(&mutex_b);

    // Seção crítica onde ambos os mutexes A e B estão bloqueados
    printf("Thread 1 na seção crítica\n");

    // Desbloqueia os mutexes na ordem inversa
    pthread_mutex_unlock(&mutex_b);
    pthread_mutex_unlock(&mutex_a);

    pthread_exit(NULL);
}

// Função que será executada pela Thread 2
void *thread_func2(void *arg) {
    printf("Thread 2 tentando bloquear mutex B\n");
    // Thread 2 tenta bloquear o mutex B
    pthread_mutex_lock(&mutex_b);
    sleep(1);

    printf("Thread 2 tentando bloquear mutex A\n");
    // Thread 2 tenta bloquear o mutex A
    pthread_mutex_lock(&mutex_a);

    // Seção crítica onde ambos os mutexes B e A estão bloqueados
    printf("Thread 2 na seção crítica\n");

    // Desbloqueia os mutexes na ordem inversa
    pthread_mutex_unlock(&mutex_a);
    pthread_mutex_unlock(&mutex_b);

    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;

    // Criação das threads
    pthread_create(&thread1, NULL, thread_func1, NULL);
    pthread_create(&thread2, NULL, thread_func2, NULL);

    // Espera pelas threads terminarem
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
