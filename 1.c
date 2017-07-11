#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include <list>
#include <arpa/inet.h>
using namespace std;

class MLogRec{
public:
	char logname[32];
	char  userip[32];
	int logintime;
	int logouttime;
	int duration;

	MLogRec(const char *name,const char *ip,int intime,int outtime,int dur){
		strcpy(logname,name);
		strcpy(userip,ip);
		logintime = intime;
		logouttime = outtime;
		duration = dur;
	}
	MLogRec(){
		
	}
};
class LogRec{
public :
	char	m_logname[32];
	int		m_pid;
	ushort	m_type;
	int		m_logintime;
	int		m_logouttime;
	char	m_ip[32];
};

list<LogRec> m_logins;
list<LogRec> m_logouts;
list<MLogRec> m_logs;

   
void match(){
	list<LogRec>::iterator begin,end = m_logouts.end();
	bool bFind = false;
	for(begin = m_logouts.begin();begin != end; )
	{
		for(list<LogRec>::iterator inbegin = m_logins.begin();
			inbegin != m_logins.end();
			inbegin++) {
			if(strcmp(begin->m_ip,inbegin->m_ip) == 0
				&& strcmp(begin->m_logname,inbegin->m_logname) == 0) {
				m_logs.push_back(MLogRec(begin->m_logname,begin->m_ip,
					inbegin->m_logintime,begin->m_logouttime,
					begin->m_logouttime - inbegin->m_logintime));
				m_logins.erase(inbegin);
				begin = m_logouts.erase(begin);
				break;
			}
		}
		if(!bFind)
		{
			begin ++;
		}
	}
}

int main(){
	string m_logFile = "wtmpx";
	//ifstream ifs(m_logFile.c_str(),ios::binary);
	LogRec 	tempLogRec;
	int len;
	ifstream ifs(m_logFile.c_str(),ios::binary);
	if(!ifs){
		cout<<"failed to access file"<<endl;
		return -1;
	}else{
		struct stat st;
		stat(m_logFile.c_str(),&st);
		cout<<"file size :"<<st.st_size<<endl;
		int i;
		len = st.st_size / 372;
		for(i = 0;i<len;i++){
			// 用户登录名
			ifs.seekg(i*372,ios::beg);
			
			ifs.read(tempLogRec.m_logname,sizeof(tempLogRec.m_logname));
			

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
			} else if(8 == tempLogRec.m_type){
				tempLogRec.m_logouttime = tempLogRec.m_logintime;
				m_logouts.push_back(tempLogRec);
			}
		}
	}

	printf("%d\t%d\t%d\t%d\n", len,m_logins.size(),m_logouts.size(),m_logs.size());
	match();

	printf("%d\t%d\t%d\t%d\n", len,m_logins.size(),m_logouts.size(),m_logs.size());

}
