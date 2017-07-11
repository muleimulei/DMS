
#ifndef __ServerSocket_H__
#define __ServerSocket_H__

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include "OracleDao.h"
#include "ClientThread.h"
class ServerSocket{
private:
	int m_sockfd;
public:
		ServerSocket(string const &ip, short port){
			//1.获取描述符
			m_sockfd = socket(AF_INET, 
		    			SOCK_STREAM, 0);
			if(-1 == m_sockfd){
		    	printf("%s\n", strerror(errno));
		    	return;
			}
			//2.准备通信地址
			struct sockaddr_in addr;
			addr.sin_family = AF_INET;
			addr.sin_port = htons(port);
			addr.sin_addr.s_addr 
			    = inet_addr(ip.c_str());
			//3.bind通信地址
			int ret = bind(m_sockfd, 
			    (struct sockaddr*)&addr,
			    sizeof(addr));
			    if(-1 == ret) {
			        printf("%s\n", strerror(errno));
			        return;
			    }
		}
	void acceptClient(){
		 //4.设置监听
		listen(m_sockfd, 100);
		//5.等待客户端的连接
		 while(1) {
            struct sockaddr_in clientAddr;
            socklen_t len = sizeof(clientAddr);
            int accfd = accept(m_sockfd, 
                (struct sockaddr*)
                &clientAddr, &len);
            if(-1 == accfd){
                printf("%s\n", strerror(errno));
                close(accfd);
                return;
            }
            LogThread* logthread = new ClientThread(accfd);
            logthread->start();
        }
	}

	~ServerSocket(){
		close(m_sockfd);
	}
	
};

#endif