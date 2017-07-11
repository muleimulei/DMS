#ifndef __EXCEPT_H__
#define __EXCEPT_H__

#include <iostream>
#include <string.h>
#include <exception>
using namespace std;

class ClientException:public exception
{
	private:
		string m_msg;
	public:
		ClientException():m_msg("�͑��ˮ���"){}
		ClientException(string const& msg):m_msg("�ͻ����쳣")
	{
		m_msg += msg;
		m_msg += "!";
	}
		~ClientException()throw(){}
		char const* what()throw()
		{
			return m_msg.c_str();
		}
};

class BackupException:public ClientException
{
	public:
		BackupException():ClientException("�����쳣"){}
		BackupException(string const& msg):ClientException(msg){}
};

class SendException:public ClientException
{
	public:
		SendException():ClientException("���������쳣"){}
};

class ReadException:public ClientException
{
	public:
		ReadException():ClientException("��ȡ��־�ļ��쳣"){}
		ReadException(string const& msg):ClientException(msg){}
};

class SocketException:public ClientException
{
	public:
		SocketException():ClientException("�������������쳣"){}
		SocketException(string const& msg):ClientException(msg){}
};

class SaveException:public ClientException
{
	public:
		SaveException():ClientException("������־�ļ��쳣"){}
		SaveException(string const& msg):ClientException(msg){}
};
#endif
