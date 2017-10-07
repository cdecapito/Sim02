// Program Information ////////////////////////////////////
/**
  * @file simFuncs.cpp
  *
  * @brief implementation of simulation, simulates 
  *        processes and threading    
  * 
  * @details splits meta data into processes and outputs data
  *
  * @version 1.00 Carli DeCapito
  *		     Original Document (10/6/17)
  *
  * @note None
  */

// Header Files
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include "data.h"
#include "process.h"
#include "memoryFunctions.h"

using namespace std;

// Global Constants
static const int NEW = 0;
static const int READY = 1;
static const int RUNNING = 2;
static const int WAITING = 3;
static const int TERMINATED = 4;


//function definitions
void splitMetaData( vector<process> &pdata, 
					vector<metaData> mdata );

void logData( configData cdata, 
			   vector<process> pdata );

bool logProcessingData( process &proc, 
						configData cdata, 
						bool monitor, 
						bool file, 
						double &time, 
						ofstream &fout );

bool getStartString( metaData mdata, 
					 char string[], 
					 double &time, 
					 process &proc );

void getEndString( metaData mdata, 
				   char string[], 
				   double &time,
				   process &proc,
				   configData cdata );

void timer( double &time,
			int timeInterval );

void* runner( void *param );

void addDelay( double &time,
			   int threadTime );

int getWaitTime( timeval startTime );




//function implementation /////////////////////////////////
/**
 * @brief 
 *
 * @details 
 *          
 * @pre 
 *
 * @post 
 *
 * @par Algorithm 
 *      
 *      
 * @exception None
 *
 * @param [in] 
 *
 * @param [out] 
 *
 * @return None
 *
 * @note None
 */
void splitMetaData( vector<process> &pdata, 
					vector<metaData> mdata )
{
	queue<metaData> tempData;
	process tempProcess;
	metaData tempMeta;
	int index;
	int processIndex = 1;
	int metaSize = mdata.size();

	for ( index = 0; index < metaSize; index++ )
	{
		//extract data and push onto
		tempMeta = mdata[ index ];

		tempData.push( tempMeta );

		//check if new process start or end
		if ( tempMeta.metaCode == 'S' || tempMeta.metaCode == 'A' )
		{
			//push onto process vector
			if( tempMeta.metaCode == 'S' &&
				strcmp( tempMeta.metaDescriptor, "end" ) == 0 )
			{
				pdata[ pdata.size() - 1 ].metadata.push( tempMeta );
			}
			//add new process
			if( tempMeta.metaCode == 'A' &&
				strcmp( tempMeta.metaDescriptor, "end" ) == 0 )
			{
				tempProcess.changeState( NEW );
				tempProcess.processNum = processIndex;
				processIndex++;
				tempProcess.metadata = tempData;

				pdata.push_back( tempProcess );

				while( !tempData.empty() )
				{
					tempData.pop();
				}
			}
		}
	}
}

/**
 * @brief 
 *
 * @details 
 *          
 * @pre 
 *
 * @post 
 *
 * @par Algorithm 
 *      
 *      
 * @exception None
 *
 * @param [in] 
 *
 * @param [out] 
 *
 * @return None
 *
 * @note None
 */
void logData( configData cdata, 
			  vector<process> pdata )
{
	bool file = false;
	bool monitor = false;
	bool processingValid = false;
	int index;
	int processSize = pdata.size();
	double time = 0.0;
	ofstream fout;

	if( strcmp( cdata.logInfo, "Log to Both" ) == 0 )
	{
		file = monitor = true;
	}
	else if ( strcmp( cdata.logInfo, "Log to File" ) == 0 )
	{
		file = true;
	}
	else if ( strcmp( cdata.logInfo, "Log to Monitor" ) == 0 )
	{
		monitor = true;
	}
	else
	{
		cout << "Error. Invalid Logging Information: " 
			 << cdata.logInfo << endl; 
	}
	//check if logging to file
	if( file == true )
	{
		//if file path was not given, report error and return
		if ( cdata.logFilePath[ 0 ] == '\0' )
		{
			cout << "Error. Missing File Path" << endl;
			return;
		}
		//otherwise open file
		fout.open( cdata.logFilePath );
	}

	for ( index = 0; index < processSize; index++ )
	{
		pdata[ index ].changeState( RUNNING );

		processingValid = logProcessingData( pdata[ index ], cdata, monitor, file, time, fout );

		if ( !processingValid )
		{
			fout.close();
			return;
		}
		pdata[ index ].changeState( TERMINATED );

		/////log processing data here ///////////
	}
	fout.close();
}


/**
 * @brief 
 *
 * @details 
 *          
 * @pre 
 *
 * @post 
 *
 * @par Algorithm 
 *      
 *      
 * @exception None
 *
 * @param [in] 
 *
 * @param [out] 
 *
 * @return None
 *
 * @note None
 */
bool logProcessingData( process &proc, 
						configData cdata, 
						bool monitor, 
						bool file, 
						double &time, 
						ofstream &fout )
{
	metaData currMetaData;
	bool dataValid;
	bool check = false;
	char startStr[ STR_LEN ];
	char endStr[ STR_LEN ];
	char errorStr[ STR_LEN ];
	queue<metaData> mdata = proc.metadata;

	while( !mdata.empty() )
	{
		//get current metadata
		currMetaData = mdata.front();
		mdata.pop();

		//check that the data is valid
		dataValid = currMetaData.errorCheck( errorStr, cdata );

		if( dataValid )
		{
			check = getStartString( currMetaData, startStr, time, proc );

			if( monitor ) 
			{
				cout << startStr << endl;
				/*
				if ( currMetaData.metaCode == 'S' )
				{
					if( proc.processNum == 1 )
					{
						cout << startStr << endl;
					}
					else if ( strcmp( currMetaData.metaDescriptor, "end" ) == 0 )
					{
						cout << startStr << endl;
					}
				}
				else
				{
					cout << startStr << endl;
				}
				*/
			}
			if( file )
			{
				fout << startStr << endl;
				/*
				if( currMetaData.metaCode == 'S' )
				{
					if( proc.processNum == 1 )
					{
						fout << startStr << endl;
					}
					else if ( strcmp( currMetaData.metaDescriptor, "end" ) == 0 )
					{
						fout << startStr << endl;
					}
				}
				else
				{
					fout << startStr << endl;
				}
				*/
			}
			if ( check )
			{
				getEndString( currMetaData, endStr, time, proc, cdata );

				if ( monitor )
				{
					cout << endStr << endl;
				}
				if ( file )
				{
					fout << endStr << endl;
				}
				
			}
		}
		else 
		{
			cout << errorStr << endl;
			return false;
		}
	}
	return true;
}


/**
 * @brief 
 *
 * @details 
 *          
 * @pre 
 *
 * @post 
 *
 * @par Algorithm 
 *      
 *      
 * @exception None
 *
 * @param [in] 
 *
 * @param [out] 
 *
 * @return None
 *
 * @note None
 */
bool getStartString( metaData mdata, 
					 char string[], 
					 double &time, 
					 process &proc)
{
	//initalize functions and variables
	char tempStr[ STR_LEN ];
	char timeStr[ STR_LEN ];
	pthread_t tid;
	int metaTime = mdata.time;
	int* threadTime = &metaTime;
	
	//get time
	sprintf( timeStr, "%f", time );
	strcpy( string, timeStr );
	strcat( string, " - " );

	//convert process number to string
	sprintf( tempStr, "%d", proc.processNum );

	//get string to output process number
	if( mdata.metaCode != 'S' && mdata.metaCode != 'A' )
	{
		strcat ( string, "Process " );
		strcat ( string, tempStr );
		strcat ( string, ": " );
	}

	//get rest of string
	mdata.getStartString( string, tempStr );

	//check for I/O metadata
	if ( mdata.metaCode == 'I' || mdata.metaCode == 'O' )
	{
		//change PCB state to waiting
		proc.changeState ( WAITING );

		//create thread to do IO 
		pthread_create( &tid, NULL, runner, threadTime );

		//wait for thread to finish
		pthread_join( tid, NULL );

		//add delay
		addDelay( time, *threadTime );

		//change pcb state to running
		proc.changeState ( RUNNING );

		return true;
	}

	timer( time, mdata.time );

	if ( ( mdata.metaCode == 'S' ) ||
		 ( mdata.metaCode == 'A' && 
		 strcmp( mdata.metaDescriptor, "end" ) == 0 ) )
	{
		return false;
	}
	return true;
}


/**
 * @brief 
 *
 * @details 
 *          
 * @pre 
 *
 * @post 
 *
 * @par Algorithm 
 *      
 *      
 * @exception None
 *
 * @param [in] 
 *
 * @param [out] 
 *
 * @return None
 *
 * @note None
 */
void getEndString( metaData mdata, 
				   char string[], 
				   double &time,
				   process &proc,
				   configData cdata )
{
	char tempStr[ STR_LEN ];
	char timeStr[ STR_LEN ];
	char memStr[ STR_LEN ];
	unsigned int address;

	//get time in string 
	sprintf( timeStr, "%f", time );
	strcpy( string, timeStr );
	strcat( string, " - " );

	//convert process number to string
	sprintf( tempStr, "%d", proc.processNum );

	//check that code is not S or A
	if ( mdata.metaCode != 'S' && mdata.metaCode != 'A' )
	{
		strcat( string, "Process " );
		strcat( string, tempStr );
		strcat( string, ": " );

	}
	if( mdata.metaCode == 'M' )
	{
		//memory allocation
		address = allocateMemory( cdata.sysMemory );
		sprintf( memStr, "%d", address );
	}

	//get rest of string data
	mdata.getEndString( string, tempStr, memStr );
}

/**
 * @brief 
 *
 * @details 
 *          
 * @pre 
 *
 * @post 
 *
 * @par Algorithm 
 *      
 *      
 * @exception None
 *
 * @param [in] 
 *
 * @param [out] 
 *
 * @return None
 *
 * @note None
 */
void timer( double &time,
			int timeInterval )
{
	timeval startTime, endTime; 
	int secs, usecs;
	double tempTime;

	//get current time
	gettimeofday( &startTime, NULL );

	while( getWaitTime( startTime ) < timeInterval );

	gettimeofday( &endTime, NULL );

	//time in secs and usecs
	secs = endTime.tv_sec - startTime.tv_sec;
	usecs = endTime.tv_usec - startTime.tv_usec;

	if( usecs < 0 )
	{
		//add 1 sec worth of microsecs
		usecs += 1000000;

		//take one sec away from secs
		secs -= 1;
	}
	if( usecs > 999999 )
	{
		secs += 1;
		usecs -= 1000000;
	}

	tempTime = ( double ) usecs / 1000 / 1000;
	time = time + ( double ) secs + tempTime; 
}

/**
 * @brief 
 *
 * @details 
 *          
 * @pre 
 *
 * @post 
 *
 * @par Algorithm 
 *      
 *      
 * @exception None
 *
 * @param [in] 
 *
 * @param [out] 
 *
 * @return None
 *
 * @note None
 */
void* runner( void *param )
{
	int secs, usecs;
	timeval startTime, endTime;

	gettimeofday( &startTime, NULL );

	while( getWaitTime( startTime ) < * ( int* ) param );
	
	gettimeofday( &endTime, NULL );

	secs = endTime.tv_sec - startTime.tv_sec;

	usecs = endTime.tv_usec - startTime.tv_usec;


	if ( usecs < 0 )
	{
		//add 1 sec
		usecs += 1000000;

		//subtract 1 sec
		secs -= 1;
	}
	if ( usecs > 999999 )
	{
		//add 1 sec
		usecs -= 1000000;

		//subtract 1 sec
		secs += 1;	
	}

	*( int* )param = secs * ( 1000000 ) + usecs;

	pthread_exit( 0 );
}


/**
 * @brief 
 *
 * @details 
 *          
 * @pre 
 *
 * @post 
 *
 * @par Algorithm 
 *      
 *      
 * @exception None
 *
 * @param [in] 
 *
 * @param [out] 
 *
 * @return None
 *
 * @note None
 */
void addDelay( double &time,
			   int threadTime )
{
	double temp = ( double ) threadTime / 1000 / 1000; 

	time += temp;
}


/**
 * @brief 
 *
 * @details 
 *          
 * @pre 
 *
 * @post 
 *
 * @par Algorithm 
 *      
 *      
 * @exception None
 *
 * @param [in] 
 *
 * @param [out] 
 *
 * @return None
 *
 * @note None
 */
int getWaitTime( timeval startTime )
{
	timeval time;
	int usecs, secs;

	gettimeofday( &time, NULL );

	//extract secs and microsecs
	secs = time.tv_sec - startTime.tv_sec;
	usecs = time.tv_usec - startTime.tv_usec;

	if ( usecs < 0 )
	{
		// add 1 sec
		usecs += 1000000;
		//subtract 1 sec
		secs -= 1;
	}
	if( secs >  0 )
	{
		usecs = usecs + ( secs * 1000000 );
	}
	return usecs;
}

