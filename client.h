
#ifndef __Client_H__
#define __Client_H__

#include <stdio.h>
#include "LogSender.h"
#include "SocketSender.h"
#include "LogReader.h"
class Client{
private:
	LogReader &m_reader;
	LogSender &m_sender;
public:
	Client(LogReader &reader,LogSender &sender):m_reader(reader),m_sender(sender){
		
	}
	void dataMine(void) throw (ClientException){
		m_sender.sendLog(m_reader.readLog());
	}
};


#endif
