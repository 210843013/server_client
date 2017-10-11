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
	int sockfd;
	struct sockaddr_in server,ser;
        
	char buf[100]="hello  udp \n";
	char buf1[100];
	int length,rv,len; 
	
	if(( sockfd = socket(AF_INET,SOCK_DGRAM,0)) < 0 )
	{
		perror("socket error");
		return -1;
	}
	
	bzero(&server, sizeof(server));
	server.sin_family=AF_INET;
	//server.sin_addr.s_addr =inet_addr("127.0.0.1");
	server.sin_port=htons(8888);
	inet_pton(AF_INET,"192.168.122.1",&server.sin_addr.s_addr);
        
        length=sizeof(struct sockaddr_in);
	sendto(sockfd,buf,strlen(buf),0,(struct sockaddr*)&server,length);
        
        rv=recvfrom(sockfd,buf1,100,0,(struct sockaddr*)&ser,&len);
	if(rv<0)
	{
	  perror("recvfrom error.");
      	  return -1;
        }	
	printf("buf1:%s",buf1);

        close(sockfd); 

return 0;

}



