# server client 
                 
		 客户端与服务器之间的通信
		 
		 
			 1、创建共享内存
			 2、将内存映射到地址中
		
		服务器(server)：
			
			 1、通过getpid(),将客户端的pid写入共享内存
			 2、pause(); -- > 等待客户端获取服务器端的pid
			 3、从共享内存中获取客户端的pid
		
		客户端(client):
		
			 1、客户端获取服务器端的pid
			 2、将服务器端的pid 通过getpid()写入共享
			 
    
     #创建内存共享并添加到地址映射后，先运行server程序，先获取客户端的pid，并写入共享内存，再等client端获取服务器端的pid并写入内存中，最后服务器端从共享内存中读取客户端的pid，服务器端开始执行写入数据的操作，写数据完毕，服务器端发送了SIGNAL信号给客户端，开始执行读共享内存的操作，读数据完毕，客户端发送一个SIGNAL信号给服务器端等待写数据操作。
     
      开始创建共享内存，并映射到地址空间，server开始写数据
      
![image](https://github.com/210843013/server_client/blob/master/start.png)
    
      client等待接收数据，并接收到数据
      
![image](https://github.com/210843013/server_client/blob/master/writeandreceive.png)

