#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

sem_t road;

void* car(void* arg){

    printf("(%lu)I INTEND to pass the fork!\n",pthread_self());
    sleep(1);

    sem_wait(&road);

    printf("(%lu)I am AT the fork!\n",pthread_self());
    sleep(1);

    printf("(%lu)I have PASSED the fork!\n",pthread_self());
    sleep(1);

    sem_post(&road);

    pthread_exit(0);
}

int main(int argc,char const *argv[])
{
    pthread_t tid[5];

    sem_init(&road,0,2);

    for(int i=0; i<5; i++){
        pthread_create(tid+i,NULL,car,NULL);
    }

    for(int i=0; i<5; i++){
        pthread_join(tid[i],NULL);
    }

    return 0;
}