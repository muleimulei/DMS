#include "client.h"
int main()
{
	LogReader	MyLogReader("wtmpx","wtmpx.loginsfail","wtmpx.fail");
	SocketSender	MySocketSender("wtmpx.fail","127.0.0.1",8888);
	Client		MyClient(MyLogReader,MySocketSender);
	MyClient.dataMine();
	return 0;
}
