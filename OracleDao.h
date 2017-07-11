#ifndef __OracleDao_H__
#define __OracleDao_H__
#include "LogDao.h"
#include <string>
#include "MLogRec.h"
#include <stdio.h>
class OracleDao:public LogDao{
public:
	OracleDao (const char * user, const char *passwd){
		//bool flag = dbOper.ConnToDB('Provider=OraOLEDB.Oracle.1;Persist Security Info = True;DataSource=XXX',user,passwd);
		// EXEC SQL CONNECT:user IDENTIFIED BY:passwd;
		// if(!flag){
		// 	printf("connect fail");
		// }
		printf("username: %s  userPasswd: %s\n",user,passwd);
	}

	void insert(MLogRec const &log){
		// char sql[128];
		// sprintf(sql,"insert into LOGS values (%s, %s, %d, %d, %d)", log.logname,log.userip, log.loginTime, log.logoutTime, log.duration);
		//  _RecordsetPtr pRst;
		//  pRst = dbOper.ExecuteWithResSQL(sql);
		//  if(NULL != pRst){
		//  	printf("insert success");
		//  }
		printf("insert success %s %s %d %d %d \n",log.logname,log.userip,log.logintime, log.logouttime,log.duration);
	}
};

#endif