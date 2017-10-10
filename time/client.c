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
	struct sockaddr_in servaddr;
	char buf[100];
	int bytes;
	
	if(( sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0 )
	{
		perror("socket error");
		return -1;
	}
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family		=		AF_INET;
	servaddr.sin_addr.s_addr=		inet_addr("127.0.0.1");
	servaddr.sin_port		=		htons(8888);
	
	if( connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) < 0 )
	{
		perror("connect error");
		return 0;
	}
	
	bytes = read(sockfd, buf, 100);
	if(bytes < 0){
		printf("Error, read failed.\n");
		return -1;
		}

	if(0 == bytes){
		printf("Server close connection.\n");
		return -1;
		}

	printf("Read bytes %d\n", bytes);
	printf("Time:%s\n", buf);
	
	close(sockfd);


}



