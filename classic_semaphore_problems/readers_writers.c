#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

sem_t file,mutex;
int readercount = 0;

char filecontent[200] = "Hello World!"; // 使用字符数组存储字符串

void* reader(void* args){

    sem_wait(&mutex);
    readercount++;
    if(readercount==1){
        sem_wait(&file); //P(file)
    }
    sem_post(&mutex);

    printf("file-content: %s\n",filecontent);

    sem_wait(&mutex);
    readercount--;
    if(readercount==0){
        sem_post(&file); //V(file)
    }
    sem_post(&mutex);

    return 0;
}

void* writer(void* args){

    sem_wait(&file);

    strcat(filecontent, " World!");
    //printf("Finish Writing!\n");

    sem_post(&file);

    return 0;
}

int main(void){
    
    sem_init(&file,0,1); //one file 
    sem_init(&mutex,0,1); 

    pthread_t readers_pthread[10],writers_pthread[10];

    for(int i = 0; i < 10; i++){
        pthread_create(readers_pthread+i,NULL,reader,NULL);
        pthread_create(writers_pthread+i,NULL,writer,NULL);
    }

    for(int i = 0; i < 10; i++){
        pthread_join(readers_pthread[i],NULL);
        pthread_join(writers_pthread[i],NULL);
    }

    sem_destroy(&file);
    sem_destroy(&mutex);

    return 0;
}