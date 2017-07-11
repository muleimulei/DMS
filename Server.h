
#ifndef __Server_H__
#define __Server_H__

#include "ServerSocket.h"
#include "StoreThread.h"

class Server{
private:
	ServerSocket m_socket;
	StoreThread m_thread;
public:
	Server(LogDao &dao,string const ip,short port)
	:m_socket(ip,port),
	m_thread(dao){
		
	}
	/**
	 * 启动服务器端数据采集
	 */
	void dateMine(){
		m_thread.start();
		m_socket.acceptClient();
	}
};


#endif