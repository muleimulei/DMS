server:main.o #OracleDao.h
	g++  main.o  -lpthread clntsh  -o server
client:clientmain.o
	g++ clientmain.o -o client
main.o:main.cpp
	g++ -c main.cpp -o main.o -lpthread -std=c++11
clientmain.o:clientmain.cpp
	g++ -c clientmain.cpp


OracleDao.h:OracleDao.pc
	proc OracleDao.pc oname=OracleDao.h code=cpp parse=none


clean:
	rm *.o server client