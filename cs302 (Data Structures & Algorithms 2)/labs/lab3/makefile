CC = g++
CFLAGS = -Wall

all: Crypto 

Crypto: Crypto.cpp Support.h Support.o
	$(CC) $(CFLAGS) -o $@ Crypto.cpp Support.cpp

.cpp.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f Crypto Support.o
	rm -f *_wmsg*.ppm
