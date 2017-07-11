
#ifndef _FileDao_H__
#define _FileDao_H__

#include <ofstream>
#include "LogDao.h"
#include "MLogRec.h"


class FileDao : public LogDao{
private:
	ofstream m_ofs;
public:
	void insert(MLogRec const &log){
		
	}
	public FileDao(string const & dbFile)
	{
		
	}
};


#endif