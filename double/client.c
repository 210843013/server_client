/*************************************************************************
	> 文件名: shmid.c
	> 作者:孙
        > 文件描述: 创建共享内存,实现非AB进程之间的读写操作
	> 邮箱:hnsyssz@gmail.com
	> 创建时间: 2017年09月14日 星期四 20时38分28秒
 ************************************************************************/
#include "sys/types.h"
#include "sys/shm.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
struct mybuf
{
    int pid;
    char buf[128];
};
struct mybuf *p;
void myfun(int signum)
{
     printf("客户端收到服务器端的数据：%s\n",p->buf);
}
int main()
{
    int shmid;
    int key;
    int pid;

    //创建共享内存
    key = ftok("share.c",'a');
    if(key<0)
    {
        printf(" 创建key失败！\n");
        return -1;
    }
    printf("创建key成功!\n");

    shmid=shmget(key,128,IPC_CREAT | 0777);

    if(shmid <0)
    {
        printf("创建共享内存失败\n");
        return  -1;
    }
    printf("创建共享内存成功 shmid=%d\n",shmid);


    //首先将进程映射到p
    signal(SIGUSR1,myfun);
    p=(struct mybuf*)shmat(shmid,NULL,0);
    //失败返回
    if(p==NULL)
    {
        printf("客户端地址映射失败！\n");
        return -2;
    }
    //获取server的PID
    pid=p->pid; // 读服务器段的pid
    p->pid=getpid(); //将客户端的pid写入共享内存
    kill(pid,11);
    while(1)
    {
           printf("客户端开始写数据:\n");
           fgets(p->buf,128,stdin);
           kill(pid,SIGUSR2);
    }

    shmdt(p);
    shmctl(shmid,IPC_RMID,NULL);

    return 0;


}
