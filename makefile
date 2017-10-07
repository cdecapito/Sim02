CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

Sim02 : Sim02.o data.o process.o memoryFunctions.o
	$(CC) $(LFLAGS) Sim02.o data.o process.o memoryFunctions.o -pthread -o Sim02

Sim02.o : Sim02.cpp data.cpp process.cpp readData.cpp simFuncs.cpp memoryFunctions.c
	$(CC) $(CFLAGS) Sim02.cpp 

data.o : data.cpp data.h
	$(CC) $(CFLAGS) data.cpp

process.o: process.cpp process.h
	$(CC) $(CFLAGS) process.cpp

memoryFunctions.o: memoryFunctions.c memoryFunctions.h
	$(CC) $(CFLAGS) memoryFunctions.c

clean: 
	\rm *.o Sim02