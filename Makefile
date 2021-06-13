CC=gcc
CFLAGS=-Wall -ansi -lreadline 
LDFLAGS=-lm
DEPS=bitarray.h filter.h hashTable.h
OBJ=bitarray.o filter.o hashTable.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bitarray: main.c $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJ) bitarray filter
