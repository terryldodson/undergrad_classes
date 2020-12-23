CC = g++
CFLAGS = -g --std=c++11
BIN = Mazemake Mazesolve

all: $(BIN)

Mazemake: Mazemake.cpp dset.cpp
	$(CC) $(CFLAGS) -o $@ $^

Mazesolve: Mazesolve.cpp
	$(CC) $(CFLAGS) -o $@ $^

clean:
	@rm -f $(BIN)


