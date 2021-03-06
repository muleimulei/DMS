#ifndef __EXCEPT_H__
#define __EXCEPT_H__
#include <iostream>
using namespace std;
class ServerException:public exception
{
	private:
		string m_msg;
	public:
		ServerException():m_msg("服务端异常"){}
		ServerException(string const& msg):m_msg("服务端异常")
	{
		m_msg += msg;
		m_msg += "!";
	}
		~ServerException()throw(){}
		char const* what()throw()
		{
			return m_msg.c_str();
		}
};

class SocketException:public ServerException
{
	public:
		SocketException():ServerException("服务端链接异常"){}
		SocketException(string const& msg):ServerException(msg){}
};

class ThreadException:public ServerException
{
	public:
		ThreadException():ServerException("服务端线程建立异常"){}
		ThreadException(string const& msg):ServerException(msg){}
};

class DBException:public ServerException
{
	public:
		DBException():ServerException("服务端数据库链接异常"){}
		DBException(string const& msg):ServerException(msg){}
};

#endif
