CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

Sim02 : Sim02.o data.o process.o readData.o
	$(CC) $(LFLAGS) Sim02.o data.o process.o readData.o -o Sim02

Sim02.o : Sim02.cpp data.cpp process.cpp readData.cpp
	$(CC) $(CFLAGS) Sim02.cpp 

data.o : data.cpp data.h
	$(CC) $(CFLAGS) data.cpp

process.o: process.cpp process.h
	$(CC) $(CFLAGS) process.cpp

clean: 
	\rm *.o Sim02