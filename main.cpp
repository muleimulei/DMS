#include "Server.h"
// #include "OracleDao.h"
#include "FileDao.h"
int main()
{
	// OracleDao myoracle("system","open123");
	FileDao filedao ("data");
	printf("Hello\n");
	Server myServer(filedao,"127.0.0.1",8888);
	printf("world\n");
	myServer.dateMine();
	return 0;
}