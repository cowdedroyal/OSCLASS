#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
	pid_t cid; //用于保存pid
	//getpid() can get processes'id number
	printf("Before fork Process id :%d\n",getpid());
	
	cid = fork();
	//如果是父进程，则返回子进程的pid
	//如果是子进程，则返回0
	printf("After fork, Process id :%d\n",getpid());

	if(cid == 0){
		printf("Child process id (parent pid is %d): %d\n",getppid(),getpid());
		for(int i=0;i<3;i++)
			printf("hello\n");
		sleep(3); //->waiting->ready
	}else{
		printf("Parent process id :%d\n",getpid());
		for(int i=0;i<3;i++)
			printf("world\n");
		//wait(NULL); //等待子进程结束再返回->waiting->ready
	}
	//孤儿进程->托管给系统进程 pid = 1371
	pause(); //使程序暂停
	
	return 0;
}
