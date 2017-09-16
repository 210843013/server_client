# server client 
                  客户端与服务器之间的通信
		  
			 1、创建共享内存
			 2、将内存映射到地址中
		
		服务器(server)：
			
			 1、通过getpid(),将客户端的pid写入共享内存
			 2、pause(); -- > 等待客户端获取服务器端的pid
			 3、从共享内存中获取客户端的pid
		
		客户端(client):
		
			 1、从共享获取服务器端的pid
			 2、将服务器端的pid 通过getpid()写入共享

