CC=g++
CFLAGS=-Wall -I /usr/local/include -I /home/kyler/projects/libraries -std=c++11
LFLAGS=-L /usr/local/lib -L /usr/lib -l nfc -l freefare -l restclient-cpp

all: test

test: rfidhandler.o main.o
	$(CC) -o test client.o rfidhandler.o main.o $(CFLAGS) $(LFLAGS) -DCURL_STATICLIB /usr/lib/x86_64-linux-gnu/libcurl.so

client.o: client.cpp
	$(CC) -c client.cpp $(CFLAGS)

rfidhandler.o: rfidhandler.h rfidhandler.cpp client.o
	$(CC) -c rfidhandler.cpp $(CFLAGS)

main.o: rfidhandler.o
	$(CC) -c main.cpp $(CFLAGS)

clean:
	@rm -f *.o test