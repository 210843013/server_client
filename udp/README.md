
#简单的udp协议



	# 1、创建套接字       
               		socket(AF_INET,SOCK_DGRAM,0)      
			
	# 2、协议绑定
			bzero(&server, sizeof(server));
			server.sin_family = AF_INET;
			server.sin_port   = htons(8888);
			server.sin_addr.s_addr  = htonl(INADDR_ANY);
	# 3、接收
	
                rv=recvfrom(sockfd,buf1,100,0,(struct sockaddr*)&client,&length); 
	# 4、发送
	
                sendto(sockfd,buf,strlen(buf),0,(struct sockaddr*)&client,length);
