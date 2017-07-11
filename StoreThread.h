
#ifndef __StoreThread_H__
#define __StoreThread_H__

#include "LogDao.h"
#include "LogThread.h"
#include "LogQueue.h"
#include "MLogRec.h"
extern LogQueue g_logqueue;
class StoreThread: public LogThread{
private:
	LogDao &m_dao;
	/**
	 * 从日志队列中取出数据，交给dao
	 * 将数据插入到数据库
	 */
	void run(){
		int num = 1;
		while(1){
			MLogRec mlogrec;
			g_logqueue >> mlogrec;
			printf("%s %s    num: %d\n",mlogrec.logname,mlogrec.userip,num);

			m_dao.insert(mlogrec);
			num++;
		}
	}
public:
	StoreThread(LogDao &dao):m_dao(dao){
	}
	
};

#endif