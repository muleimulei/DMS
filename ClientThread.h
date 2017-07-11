
#ifndef __ClientThread_H__
#define __ClientThread_H__
#include "MLogRec.h"
#include "LogQueue.h"
#include "LogThread.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
extern LogQueue 	g_logqueue;
class ClientThread : public LogThread{
private:
	int m_accfd;
	
public:
	ClientThread(int accfd){
		m_accfd = accfd;
	}
	/**
	 * 接受客户端数据
	 */
private:
	void run(){
		MLogRec log;
		while(1){
		    int ret = recv(m_accfd, &log, 
		        sizeof(MLogRec), 0);
		    if(ret < 0 || ret != sizeof(MLogRec)) {
		        close(m_accfd);
		        printf("接收失败\n");
		        return;
		    }
		    else if(ret > 0) {
		        g_logqueue << log;
		    }
    	}
	}
	~ClientThread()
	{
	}
};

#endif