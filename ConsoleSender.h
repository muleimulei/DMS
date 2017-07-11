
#ifndef __ConsoleSender_H__
#define __ConsoleSender_H__
#include "MLogRec.h"
class ConsoleSender{
public:
	void sendLog(list<MLogRec> &logs){
		list<MLogRec>::iterator it;
		for(it = logs.begin();it != logs.end();it++)
		{
			printf("%s,%s,%d,%d,%d\n",
				it->logname,
				it->userip,
				it->logintime,
				it->duration);
		}
	}
};

#endif