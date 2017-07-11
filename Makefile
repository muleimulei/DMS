server:main.o
	g++  main.o -lpthread -o server
client:clientmain.o
	g++ clientmain.o -o client
main.o:main.cpp
	g++ -c main.cpp -o main.o -lpthread -std=c++11
clientmain.o:clientmain.cpp
	g++ -c clientmain.cpp


clean:
	rm *.o
