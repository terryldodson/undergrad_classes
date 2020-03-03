#CS 360 Lab 5A Makefile

CC = gcc 

INCLUDES = -I/home/jplank/cs360/include

CFLAGS = -g $(INCLUDES)

LIBDIR = /home/jplank/cs360/objs

LIBS = $(LIBDIR)/libfdr.a 

EXECUTABLES = tarx

all: $(EXECUTABLES)

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c

tarx: tarx.c
	$(CC) $(CFLAGS) -o tarx tarx.c $(LIBS)

#make clean will rid your directory of the executable,
#object files, and any core dumps you've caused
clean:
	rm core $(EXECUTABLES) *.o


