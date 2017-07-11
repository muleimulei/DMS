#ifndef __LogRec_H__
#define __LogRec_H__
#include <string.h>
class LogRec{
public:
	char	m_logname[32];
	int		m_pid;
	unsigned short	m_type;
	int		m_logintime;
	int		m_logouttime;
	char	m_ip[32];
};
#endif
