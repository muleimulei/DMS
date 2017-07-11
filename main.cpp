#include "Server.h"
#include "OracleDao.h"
int main()
{
	OracleDao myoracle("system","open123");
	Server myServer(myoracle,"127.0.0.1",8888);
	myServer.dateMine();
	return 0;
}