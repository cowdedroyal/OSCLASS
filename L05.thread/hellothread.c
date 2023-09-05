#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

//gcc命令 gcc ***.c -o *** -pthread
void* threadFun(void* arg){//线程函数
    printf("In new thread!\n");
}

int main()
{
    pthread_t tid;

    //线程创建函数
    /*
    1.Thread id address
    2.Thread attribute address
    3.Thread function address
    4.Thread parameters address
    */
    pthread_create(&tid,NULL,threadFun,NULL);

    //等待指定线程结束
    //pthread_join(tid,NULL);

    printf("In main thread\n");

    return 0;
}