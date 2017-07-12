
#ifndef _FileDao_H__
#define _FileDao_H__

// #include <ofstream>
#include "LogDao.h"
#include "MLogRec.h"
#include <stdio.h>
#include <string>
class FileDao : public LogDao{
private:
	FILE * m_ofs;
public:
	void insert(MLogRec const &log){
		int ret = fprintf(m_ofs,"%s %s %d %d %d", log.logname,log.userip,log.logintime,log.logouttime,log.duration);
		if(ret<0){
			printf("insert error\n");
		}else{
			fputc('\n',m_ofs);
			printf("insert success\n");
		}
		
	}
	FileDao(char   dbFile[])
	{
		m_ofs = fopen(dbFile,"a+");
	}
};


#endif