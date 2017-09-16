/*************************************************************************
	> 文件名: shmid.c
	> 作者:孙 
        > 文件描述: 创建共享内存,父子进程通过共享内存实现数据的读写操作。
	> 邮箱:hnsyssz@gmail.com 
	> 创建时间: 2017年09月14日 星期四 20时38分28秒
 ************************************************************************/
#include "sys/types.h"
#include "sys/shm.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"

void myfun(int signum)
{
    return ;
}
int main()
{
  int shmid;
  int key;
  int pid;
  char *p;
  
   //创建共享内存 
  shmid=shmget(IPC_PRIVATE,128,IPC_CREAT | 0777);
  
    if(shmid <0)
  {
	printf("creat share memory failure\n");
	return -1;
  }
  printf("creat share memory sucess shmid=%d\n",shmid);
 
    pid=fork();
    if(pid>0)
    {
        //父进程执行写的操作
        //首先将进程映射到p
        signal(SIGUSR2,myfun);
        p=(char*)shmat(shmid,NULL,0);
      //失败返回
        if(p==NULL)
        {
            printf("parent process ：shmat function failure！\n");
            return -2;
        }

      //成功执行写操作
    while(1)
        {
            printf("parent process start write - - ->\n");
            fgets(p,128,stdin);
            kill(pid,SIGUSR1); //通知子进程读取数据
            pause(); //等待子进程读数据

        }
    }
   
     if(pid==0)
    {
      signal(SIGUSR1,myfun);  
      p=(char *)shmat(shmid,NULL,0);
      if(p==NULL)
        {
            printf("child process shmat function failure!\n");
            return -3;
        }
        while(1)
        {
        pause(); //等待父进程写数据 
        printf("share memory date:%s",p);
        kill(getppid(),SIGUSR2);
        }
    }
        shmdt(p);
        shmctl(shmid,IPC_RMID,NULL);
  // system("ipcs -m");
  // system("ipcrm -m shmid");
  

    return 0;
}
