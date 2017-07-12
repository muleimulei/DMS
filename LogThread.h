
#ifndef __LogThread_H__
#define __LogThread_H__
#include <pthread.h>
#include <stdio.h>

class LogThread{
public:
    
    static void* task(void* arg){
        LogThread* logthread = (LogThread*)arg;
        printf("LogThread:\t%p\n",logthread);
        logthread->run();
        delete logthread;
    }
	void start(){
		// 创建线程，与客户端进行通信
        pthread_t tid;
        int ret = pthread_create(&tid, NULL,
            task,this);
        if(-1 == ret) {
            printf("failed to create thread!\n");
            return;
        }
        else {
            printf("create thread ok!\n");
        }
	}
	
private:
	virtual void run()=0;
};


#endif