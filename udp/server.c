/*************************************************************************
	> 文件名: server.c
	> 作者:孙 
        > 文件描述: 
	> 邮箱:hnsyssz@gmail.com 
	> 创建时间: 2017年09月20日 星期三 21时00分10秒
 ************************************************************************/
#include "socket_includes.h"
int main(int argc, char *argv[])
{
	int  sockfd;
	struct sockaddr_in server, client;
	char buf[100];
	char buf1[100];
	int timep;
 	int rv;
	socklen_t len,length;
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd< 0 )
	{
		perror("socket error");
		return -1;
	}
	
	bzero(&server, sizeof(server));
  	server.sin_family = AF_INET;
  	server.sin_port   = htons(8888);
  	server.sin_addr.s_addr  = htonl(INADDR_ANY);
         
	len = sizeof(struct sockaddr);

     if(bind(sockfd, (struct sockaddr *)&server, len)<0){
      perror("bind error.");
      return -1;
  }  
  
     while(1)
{
        rv=recvfrom(sockfd,buf1,100,0,(struct sockaddr*)&client,&length);
	
        if(rv<0)
	{
	  perror("recvfrom error.");
      	  return -1;
        }	
	printf("buf1:%s",buf1);
	timep = time(NULL);
	snprintf(buf, sizeof(buf), "%s", ctime(&timep));
        sendto(sockfd,buf,strlen(buf),0,(struct sockaddr*)&client,length);
        
	bzero(&client,length);
	bzero(buf,100); 
        bzero(buf1,100);
       
}      
        close(sockfd); 
	return 0;
}




