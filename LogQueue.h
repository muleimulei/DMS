#ifndef __LogQueue_H__
#define __LogQueue_H__
#include <list>
#include "MLogRec.h"
#include <iostream>
#include <stdio.h>
using namespace std;

class LogQueue{
private:
	list<MLogRec> m_log;
	pthread_mutex_t m_mtx;
	pthread_cond_t m_notFull;
	pthread_cond_t m_notEmpty;
public:
	LogQueue &operator << (MLogRec const &log){
	    printf("insert into.... \n");

        pthread_mutex_lock(&m_mtx);
        m_log.push_back(log);

        pthread_cond_broadcast(&m_notEmpty);

        pthread_mutex_unlock(&m_mtx);
	      
	    return *this;
	}
	LogQueue &operator >> (MLogRec  &log){
		printf("take out ............\n");
        pthread_mutex_lock(&m_mtx);
        while(m_log.size()==0){
        	printf("empty: wait for not empty!\n");
        	pthread_cond_wait(&m_notEmpty, &m_mtx);
        }

        list<MLogRec>::iterator begin =  m_log.begin();
        log = *begin;
       
        m_log.erase(begin);
        
        pthread_cond_broadcast(&m_notFull);
        pthread_mutex_unlock(&m_mtx);
	       // usleep((rand () % 100) * 10000);
	    return *this;
	}
	LogQueue(){
		m_mtx = PTHREAD_MUTEX_INITIALIZER;
		m_notFull = PTHREAD_COND_INITIALIZER;
		m_notEmpty = PTHREAD_COND_INITIALIZER;
	}
};

LogQueue g_logqueue;

#endif
