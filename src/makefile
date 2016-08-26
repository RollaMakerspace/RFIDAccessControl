CC=g++
CFLAGS=-I /usr/local/include -L /usr/local/lib -L /usr/lib -l curl -l restclient-cpp -DCURL_STATICLIB /usr/lib/x86_64-linux-gnu/libcurl.so -std=c++11

sub-modules: client.cpp
	$(CC) -c client.cpp $(CFLAGS)
