#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_t philosophers[NUM_PHILOSOPHERS];
sem_t forks[NUM_PHILOSOPHERS];

void *philosopher(void *arg) {
    int id = *(int *)arg;
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;

    while (1) { //会产生死锁
        //printf("Philosopher %d is thinking\n", id);
        //sleep(1);

        //printf("Philosopher %d is hungry\n", id);
        sem_wait(&forks[left_fork]);
        sem_wait(&forks[right_fork]);

        printf("Philosopher %d is eating\n", id);
        //sleep(2);

        sem_post(&forks[left_fork]);
        sem_post(&forks[right_fork]);
    }
}

int main() {
    int i;
    int ids[NUM_PHILOSOPHERS];

    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1);
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
        sem_destroy(&forks[i]);
    }

    return 0;
}
