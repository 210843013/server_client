/*************************************************************************
	> 文件名: msg.c
	> 作者:孙 
    > 文件描述:消息队列、信号量
    相关函数:msgget(2),   msgrcv(2),   msgsnd(2) 
	> 邮箱:hnsyssz@gmail.com 
	> 创建时间: 2017年09月18日 星期一 09时16分08秒
 ************************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
struct msgbuff
{
    long type;
    char buff[124];
    char ID[4];
};

int main()
{
    // 消息队列的创建
    int msgid;
    int key;
    int pid;
    struct msgbuff sendbuff,rcvbuff;
    key=ftok("./test.c",'a');
    if(key<0)
    {
        printf("creat key failure!\n");
        return -1;
    }
    msgid = msgget(key,IPC_CREAT|0777);
    if(msgid <0)
    {
        printf("creat failue!\n");
        return -1;
    }

    printf("创建消息队列成功!\n");
    system("ipcs -q");

    //发送数据
    pid=fork(); 
  
  if(pid == 0)
    {  
    sendbuff.type=100; 
      while(1)
      {
      //每次发送前清空缓存
      memset(sendbuff.buff,0,124); 
      printf("等待接收或发送信息:\n");
      //开始发送信息
      fgets(sendbuff.buff,124,stdin);
      msgsnd(msgid,&sendbuff,strlen(sendbuff.buff),0);
      printf("发送消息完成!\n\n\n");
      //system("ipcs -q");
      }
    }

   if(pid > 0)
    {
     rcvbuff.type=100; 
     while(1)
    {
     memset(rcvbuff.buff,0,124); 
     msgrcv(msgid,(void*)&rcvbuff,124,200,0);
     printf("接收到的信息：%s\n",rcvbuff.buff); 
     printf("接收数据完成！\n"); 
     printf("等待接收或发送信息:\n"); 
    }  
   //发送数据
  
   
  }
   msgctl(msgid,IPC_RMID,NULL);

    return 0;
}


