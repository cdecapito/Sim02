CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

Sim02 : Sim02.o data.o process.o MemoryFunction.o
	$(CC) $(LFLAGS) Sim02.o data.o process.o MemoryFunction.o -pthread -o Sim02

Sim02.o : Sim02.cpp data.cpp process.cpp readData.cpp simFuncs.cpp MemoryFunction.c
	$(CC) $(CFLAGS) Sim02.cpp 

data.o : data.cpp data.h
	$(CC) $(CFLAGS) data.cpp

process.o: process.cpp process.h
	$(CC) $(CFLAGS) process.cpp

MemoryFunction.o: MemoryFunction.c MemoryFunction.h
	$(CC) $(CFLAGS) MemoryFunction.c

clean: 
	\rm *.o Sim02