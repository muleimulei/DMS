#ifndef __EXCEPT_H__
#define __EXCEPT_H__
#include <iostream>
using namespace std;
class ServerException:public exception
{
	private:
		string m_msg;
	public:
		ServerException():m_msg("������쳣"){}
		ServerException(string const& msg):m_msg("������쳣")
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
		SocketException():ServerException("����������쳣"){}
		SocketException(string const& msg):ServerException(msg){}
};

class ThreadException:public ServerException
{
	public:
		ThreadException():ServerException("������߳̽����쳣"){}
		ThreadException(string const& msg):ServerException(msg){}
};

class DBException:public ServerException
{
	public:
		DBException():ServerException("��������ݿ������쳣"){}
		DBException(string const& msg):ServerException(msg){}
};

#endif
