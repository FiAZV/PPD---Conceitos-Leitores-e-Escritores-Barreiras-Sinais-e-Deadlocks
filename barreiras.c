#include <pthread.h>   // Biblioteca para manipulação de threads POSIX
#include <stdio.h>     // Biblioteca para funções de entrada e saída
#include <stdlib.h>    // Biblioteca para funções utilitárias, como rand()
#include <unistd.h>    // Biblioteca para funções de controle de processos e sleep()

// Definição do número de threads e barreiras
#define NUM_THREADS 5
#define NUM_BARRIERS 3

// Declaração de uma variável do tipo barreira para sincronização das threads
pthread_barrier_t barrier;

/**
 * Função que será executada por cada thread.
 * Recebe como argumento um ponteiro para o ID da thread.
 */
void *thread_task(void *arg) {
    // Defininfo o ID da thread
    int id = *(int *)arg;

    // Loop que repete o processo de sincronização pelo número de barreiras definido
    for (int i = 0; i < NUM_BARRIERS; i++) {
        // Thread está antes da barreira atual e simulação de atraso
        printf("Thread %d antes da barreira %d\n", id, i + 1);
        sleep(rand() % 3);

        // Ponto de sincronização: todas as threads devem chegar aqui antes de prosseguir
        pthread_barrier_wait(&barrier);

        // Thread passou da barreira atual e simulação de atraso
        printf("Thread %d apos a barreira %d\n", id, i + 1);
        sleep(rand() % 2);
    }

    // Termina a execução da thread
    pthread_exit(NULL);
}

int main() {
    // Declaração de um array para armazenar as threads
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    // Inicialização da barreira para sincronizar NUM_THREADS threads
    pthread_barrier_init(&barrier, NULL, NUM_THREADS);

    // Criação das threads
    for (int i = 0; i < NUM_THREADS; i++) {
        // Atribui um ID único para cada thread (de 1 a NUM_THREADS)
        thread_ids[i] = i + 1;
        // Cria a thread, passando a função thread_task e o endereço do ID como argumento
        if (pthread_create(&threads[i], NULL, thread_task, &thread_ids[i]) != 0) {
            perror("Erro ao criar a thread");
            exit(EXIT_FAILURE);
        }
    }

    // Aguarda que todas as threads terminem sua execução
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destruição da barreira após o término de todas as threads
    pthread_barrier_destroy(&barrier);

    return 0;
}
