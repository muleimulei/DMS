#ifndef __LogSender_H__
#define __LogSender_H__
#include <string>
#include "MLogRec.h"
#include <list>
#include "ClientException.h"
class LogSender{
public:
	virtual void sendLog(list<MLogRec> &log) throw(ClientException) = 0;
};


#endif
