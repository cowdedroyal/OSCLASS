#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

int ticketAmount = 2; //Global Variable

sem_t mutex;

void* ticketAgent(void* arg){

    sem_wait(&mutex); //P(mutex)
    
    int t = ticketAmount;

    if(t>0)
    {
        printf("One ticket sold!\n");
        t--;
    }else{
        printf("Ticket sold out!!\n");
    }
    ticketAmount = t;

    sem_post(&mutex); //V(mutex)
    
    pthread_exit(0);
}

int main()
{
    pthread_t ticketAgent_tid[2];

    sem_init(&mutex,0,1); //mutex = 1

    for(int i=0; i<2; i++){
        pthread_create(ticketAgent_tid+i,NULL,ticketAgent,NULL);
    }

    for(int i=0; i<2; i++){
        pthread_join(ticketAgent_tid[i],NULL);
    }

    printf("The left ticket is %d\n",ticketAmount);

    sem_destroy(&mutex); //destroy mutex
    return 0;
}