#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

pthread_mutex_t resource_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t read_count_mutex = PTHREAD_MUTEX_INITIALIZER;
int read_count = 0;
int shared_data = 0;

void *reader(void *arg) {
    int id = *(int *)arg;

    while (1) {
        // Entrada da seção crítica para leitores
        pthread_mutex_lock(&read_count_mutex);
        read_count++;
        if (read_count == 1) {
            pthread_mutex_lock(&resource_mutex);
        }
        pthread_mutex_unlock(&read_count_mutex);

        // Seção crítica: leitura do recurso compartilhado
        printf("Leitor %d lendo o valor: %d\n", id, shared_data);
        sleep(1);

        // Saída da seção crítica para leitores
        pthread_mutex_lock(&read_count_mutex);
        read_count--;
        if (read_count == 0) {
            pthread_mutex_unlock(&resource_mutex);
        }
        pthread_mutex_unlock(&read_count_mutex);

        sleep(rand() % 3);
    }

    pthread_exit(NULL);
}

void *writer(void *arg) {
    int id = *(int *)arg;

    while (1) {
        // Entrada da seção crítica para escritores
        pthread_mutex_lock(&resource_mutex);

        // Seção crítica: escrita no recurso compartilhado
        shared_data = rand() % 100;
        printf("Escritor %d escrevendo o valor: %d\n", id, shared_data);
        sleep(2);

        // Saída da seção crítica para escritores
        pthread_mutex_unlock(&resource_mutex);

        sleep(rand() % 5);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

    // Criação de threads leitoras
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Criação de threads escritoras
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Junção das threads (nunca alcançado neste exemplo)
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    return 0;
}
