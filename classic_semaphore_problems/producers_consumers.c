#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
sem_t empty, full;
pthread_mutex_t mutex;

int rc = 0; //resouce_count
int rcc = 0; //already produced product

void *producer(void *arg) {
    
    //int item = rand() % 100; // Produce an item (0-99)
    sem_wait(&empty); // Wait for an empty slot in the buffer
    pthread_mutex_lock(&mutex); // Acquire the mutex

    rcc++;
    sleep(1);
    int item = rcc; //produce an item

    // Add item to the buffer
    printf("Producing %d\n", item);
    buffer[rc % BUFFER_SIZE] = item;
    //sleep(1);
    rc++;
    
    pthread_mutex_unlock(&mutex); // Release the mutex
    sem_post(&full); // Signal that a slot is full
    
    // Sleep for a random time
    //usleep(rand() % 1000000);
    return NULL;
}

void *consumer(void *arg) {
    int item;
    sem_wait(&full); // Wait for a slot to be full
    pthread_mutex_lock(&mutex); // Acquire the mutex
    
    // Consume an item from the buffer
    rc--;
    item = buffer[rc % BUFFER_SIZE];
    //printf("Consuming %d\n", item);
    
    pthread_mutex_unlock(&mutex); // Release the mutex
    sem_post(&empty); // Signal that a slot is empty
    
    // Sleep for a random time
    //usleep(rand() % 1000000);
    sleep(1);
    return NULL;
}

int main() {
    pthread_t producer_thread[10], consumer_thread[10];

    sem_init(&empty, 0, BUFFER_SIZE); // Initialize semaphore for empty slots
    sem_init(&full, 0, 0); // Initialize semaphore for full slots
    pthread_mutex_init(&mutex, NULL); // Initialize mutex
    
    // Create producer and consumer threads
    for(int i = 0; i < 10; i++){
        pthread_create(producer_thread+i, NULL, producer, NULL);
        pthread_create(consumer_thread+i, NULL, consumer, NULL);
    }
    
    for(int i = 0; i < 10; i++){
        // Join threads
        pthread_join(producer_thread[i], NULL);
        pthread_join(consumer_thread[i], NULL);
    }

    sem_destroy(&empty); // Destroy semaphores
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex); // Destroy mutex
    
    return 0;
}
