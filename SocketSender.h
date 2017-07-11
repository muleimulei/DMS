
#ifndef __SocketSender_H__
#define __SocketSender_H__
#include "LogSender.h"
#include "MLogRec.h"
#include <list>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>


class SocketSender: public LogSender{
private:
	string m_failFile;
	string m_ip;
	short m_port;
	int m_sockfd;

	void connectServer(void) throw(SocketException){
	 	//1.获取socket描述符
	    m_sockfd = socket(AF_INET, 
	        SOCK_STREAM, 0);
	    if(-1 == m_sockfd)
	    {
	        printf("%s\n", strerror(errno));
	        return ;
	    }else{
	    	printf("server fd:%d\n",m_sockfd);
		 //2.准备通信地址
	    }
	    struct sockaddr_in addr;
	    addr.sin_family = AF_INET;
	    addr.sin_port = htons(m_port);
	    addr.sin_addr.s_addr
	        = inet_addr(m_ip.c_str());
	    int ret = connect(m_sockfd, 
	        (struct sockaddr*)&addr, 
	        sizeof(addr));
	    if(-1 == ret)
	    {
	        printf("failed %s\n", strerror(errno));
	        return;
	    }


	}

	void readFailFile(list<MLogRec> &logs) throw (ReadException){
		printf("read previous fail file...........\n");

		FILE *f = fopen(m_failFile.c_str(),"w+");
		char logname[32];
		char userIp[32];
		int loginTime;
		int logoutTime;
		int duration;

		while(!feof(f)){
			fscanf(f,"%s %s %d %d %d",logname, userIp,&loginTime,&logoutTime,&duration);
			//fread(logname, sizeof(logname), f);
			logs.push_back(MLogRec(logname,userIp,loginTime,logoutTime,duration));
		}
		fclose(f);

	}

	void sendData(list<MLogRec> &logs) throw (SendException){
		printf("send data..........%d\n",logs.size());


		list<MLogRec>::iterator it;
		int ret;
		for(it = logs.begin();it != logs.end();)
		{
			MLogRec temp = *it;
		    ret = send(m_sockfd, (void*)&temp, 
		            sizeof(MLogRec), 0);
		    if(-1 == ret)
		    {
		        printf("fail %s\n", strerror(errno));
		        break;
		    }else{
		    	it = logs.erase(it);
		    }
		}

		printf("send data end %d\n",logs.size());
	}
	void saveFailFile(list<MLogRec> &logs) throw (SaveException){
		printf("save fail data........%d\n",logs.size());
		FILE *f = fopen(m_failFile.c_str(),"a+");
		list<MLogRec>::iterator begin,end = logs.end();

		for(begin = logs.begin();begin!=end;begin++){
			fprintf(f,"%s %s %d %d %d",begin->logname,begin->userip,begin->logintime,begin->logouttime,begin->duration);
			fputc('\n',f);
		}
		fclose(f);
		printf("save fail end %d\n",logs.size());
	}
public:
	SocketSender(string const &failFile,string const &ip,short port){
		m_failFile = failFile;
		m_ip = ip;
		m_port = port;
		connectServer();
	}
	virtual void sendLog(list<MLogRec> &logs) throw (ClientException){
		readFailFile(logs);
		sendData(logs);
		saveFailFile(logs);
	}
};

#endif
