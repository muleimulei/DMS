#ifndef __LogReader_H__
#define __LogReader_H__

#include <list>
#include "LogRec.h"
#include "MLogRec.h"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <stdlib.h>
using namespace std;

class LogRec;
class MLogRec;

class LogReader{
private:
	string m_logFile;
	string m_loginsFile;
	string m_failFile;
	list< LogRec > m_logins;
	list< LogRec > m_logouts;
	list< MLogRec > m_logs;
public:
	LogReader(string const &logFile, string const &loginsFile,string const &failFile ){
		m_logFile = logFile;
		m_loginsFile = loginsFile;
		m_failFile = failFile;
	}
	list<MLogRec>& readLog(void) throw (ClientException){
		/**
		 * 备份原始日志文件
		 */
		backup();

		/**
		 * 读取上一次未匹配好的登陆日志文件
		 */

		readLoginsFile();

		/**
	 	 * 读取备份的日志文件
	 	 */
		readBackupFile();

		/**
		 * 进行匹配
		 */
		match();

		/**
		 * 将未匹配的数据写入文件 
		 */
		saveLoginsFile();
		return m_logs;
	}
	void backup(){
		time_t t = time(0); 	
		char buf[40];
		tm * time = localtime(&t);
		strftime(buf, 26, "%Y%m%d%H%M%S", time);
		m_logFile = string("wtmpx.") + buf;
		string cmd = "bash ./copy.sh wtmpx wtmpx."+string(buf);
		
		int status = system(cmd.c_str());
		int ret = WEXITSTATUS(status);
		if(1 == ret || 2 == ret) {
			printf("备份失败\n");
			exit(0);
		}
	}
	/**
	 * 读取上次未匹配的数据
	 */
    void readLoginsFile(){
		FILE *f = fopen(m_loginsFile.c_str(),"w+");
		LogRec temp;
		while(!feof(f)){
			fscanf(f,"%s %s %d %d",
				temp.m_logname, 
				temp.m_ip,
				&temp.m_pid,
				&temp.m_logintime
				);
			m_logins.push_back(temp);
		}
		fclose(f);

	}

	void readBackupFile(){
		
		// 每一条记录 372 字节
		// 得到文件大小，得到记录的个数
		LogRec 	tempLogRec;
		ifstream ifs(m_logFile.c_str(),ios::binary);
		if(!ifs){
			cout<<"failed to access file"<<endl;
			return;
		}else{
			struct stat st;
			stat(m_logFile.c_str(),&st);
			cout<<"file size :"<<st.st_size<<endl;
			int i;
			int len = st.st_size / 372;
			for(i = 0;i<len;i++){
			
				// 用户登录名
				ifs.seekg(i*372,ios::beg);
				
				ifs.read(tempLogRec.m_logname,sizeof(tempLogRec.m_logname));
				
				if(tempLogRec.m_logname[0] == '.')
				{
					continue;
				}

				// 进程ID
				ifs.seekg(i*372 + 68,ios::beg);
				
				ifs.read((char *)&tempLogRec.m_pid,sizeof(tempLogRec.m_pid));
				tempLogRec.m_pid = ntohl(tempLogRec.m_pid);
				// 登陆类型
				
				ifs.read((char *)&tempLogRec.m_type,sizeof(tempLogRec.m_type));
				tempLogRec.m_type = ntohs(tempLogRec.m_type);
				// 登陆时刻
				ifs.seekg(i*372 + 80,ios::beg);
				
				ifs.read((char *)&tempLogRec.m_logintime,sizeof(tempLogRec.m_logintime));
				tempLogRec.m_logintime = ntohl(tempLogRec.m_logintime);

				
				// 登陆IP 长度
				ifs.seekg(i*372 + 112,ios::beg);
				ushort ip_length;
				ifs.read((char *)&ip_length,sizeof(ip_length));
				ip_length = ntohs(ip_length);

				// 登陆IP
				
				ifs.read(tempLogRec.m_ip,ip_length);
				tempLogRec.m_ip[ip_length] = 0;

				if(7 == tempLogRec.m_type) {
					m_logins.push_back(tempLogRec);
				} else if( 8 == tempLogRec.m_type) {
					tempLogRec.m_logouttime = tempLogRec.m_logintime;
					m_logouts.push_back(tempLogRec);
				}
			}
		}
	}
	void match(){
		list<LogRec>::iterator begin,end = m_logouts.end();
		bool bFind = false;
		for(begin = m_logouts.begin();begin != end; )
		{
			bFind = false;
			list<LogRec>::iterator inbegin;
			for(inbegin = m_logins.begin();inbegin != m_logins.end();inbegin++) {
				if(strcmp(begin->m_ip,inbegin->m_ip) == 0
					&& strcmp(begin->m_logname,inbegin->m_logname) == 0
					&& begin->m_pid == inbegin->m_pid) {
					m_logs.push_back(MLogRec(begin->m_logname,begin->m_ip,
						inbegin->m_logintime,begin->m_logouttime,
						begin->m_logouttime - inbegin->m_logintime));
					m_logins.erase(inbegin);
					begin = m_logouts.erase(begin);
					bFind = true;
					break;
				}
			}
			if(!bFind)
			{
				begin++;
			}
		}
	}
	/**
	 * 将未匹配的m_logins写入文件m_loginsFile
	 */
	void saveLoginsFile(){
		FILE *f = fopen(m_failFile.c_str(),"w");
		list<LogRec>::iterator begin;

		for(begin = m_logins.begin();begin!=m_logins.end();begin++){
			fprintf(f,"%s %s %d %d",
				begin->m_logname,
				begin->m_ip,
				begin->m_pid,
				begin->m_logintime);
			fputc('\n',f);
		}
		fclose(f);
	}

};


#endif
