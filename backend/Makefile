CC = g++
CFLAGS = -std=c++2a


Server : main.cpp server.o
	$(CC) $(CFLAGS) -o $@ $^

server.o : server.hpp server.cpp
	$(CC) $(CFLAGS) -c server.cpp

all : clean Server

clean :
	rm -rf *.o Server
