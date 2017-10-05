// Program Information /////////////////////////////////////////////////////////
/**
  * @file process.h
  *
  * @brief   definition file of PCB and process class    
  * 
  * @details defines member functions and data members
  *
  * @version 1.00 Carli DeCapito
  *		     Original Document (10/4/17)
  *
  * @note None
  */
//precompiler directives
#ifndef PROCESS_H
#define PROCESS_H

//header files
#include <queue>
#include <vector>
#include "data.h"

using namespace std;


//PCB class definition
class PCB
{
	static const int NEW = 0;
	static const int READY = 1;
	static const int RUNNING = 2;
	static const int WAITING = 3;
	static const int TERMINATED = 4;

	public:
		//constructor
		PCB();
		//destructor
		~PCB();

		//member functions
		void setState( int newState );

		//data members
		int state;
};


//process class definition
class process
{
	public:
		//constructor
		process();
		//destructor
		~process();

		//member functions
		void changeState( int state );

		//data members
		queue<metaData> metadata;
		PCB pcb;
		int processNum;
};

#endif