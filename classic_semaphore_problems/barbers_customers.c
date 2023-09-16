#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_WAIT 5

sem_t customer,barber,c_mutex;
int waiting = 0; 

void* barbers(void* args){
    while(1){
        sem_wait(&customer);//p(customer)

        printf("Cut Hair\n");

        sem_wait(&c_mutex);
        printf("Finish Cutting Hair\n");
        waiting--;
        printf("Currently waiting number is %d\n",waiting);
        sem_post(&c_mutex);

        sem_post(&barber);

        sleep(1);
        if(waiting==0){
            break;
        }
    }
    return 0;
}

void* customers(void* args){

    sem_wait(&c_mutex);
    if(waiting < MAX_WAIT){
        waiting++;
        sem_post(&c_mutex);
        
        sem_wait(&barber);//p(barber)
        sem_post(&customer);

        return 0;
    }
    else{
        sem_post(&c_mutex);

        printf("Leave out!\n");
        return 0;
    }

}


int main(int argc,char const *argv[])
{
    sem_init(&customer,0,0);
    sem_init(&barber,0,1);
    sem_init(&c_mutex,0,1);
    pthread_t customers_pthread[10],barber_pthread;

    pthread_create(&barber_pthread,NULL,barbers,NULL);
    for(int i = 0; i < 10; i++){
        pthread_create(customers_pthread+i,NULL,customers,NULL);
    }

    for(int i = 0; i < 10; i++){
        pthread_join(customers_pthread[i],NULL);
    }
    pthread_join(barber_pthread,NULL);

    sem_destroy(&customer);
    sem_destroy(&barber);
    sem_destroy(&c_mutex);

    return 0;
}