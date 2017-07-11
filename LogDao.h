
#ifndef __LogDao_H__
#define __LogDao_H__
#include "MLogRec.h"

class LogDao{
public:
	virtual void insert(MLogRec const &log) = 0;
};

#endif