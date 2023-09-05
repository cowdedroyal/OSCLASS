#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

int value = 0;

void* hello(void* arg){
    for(int i=0; i < 3; i++)
    {
        printf("hello(%d)\n",value++);
    }
}

void* world(void* arg){
    for(int i=0; i<3; i++)
    {
        printf("world(%d)\n",value++);
    }
}

int main()
{
    srand(time(NULL));
    pthread_t tid,tid2;

    pthread_create(&tid,NULL,hello,NULL);
    pthread_create(&tid2,NULL,world,NULL);

    pthread_join(tid,NULL);
    pthread_join(tid2,NULL);
    
    printf("In main thread\n");
    return 0;
}