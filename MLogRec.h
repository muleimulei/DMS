#ifndef __MLogRec_H__
#define __MLogRec_H__
#include <string.h>

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
#endif

