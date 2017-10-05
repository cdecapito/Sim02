
//header files
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

using namespace std;

//main driver functions
bool configFileValid( char string[] );

//main driver implmentation
int main( int argc, char* argv[] )
{
	
	if( argc != 2 )
	{
		cout << "Error: Invalid Number of Command Line Arguements." << endl;
        return 0;
	}

	if( !configFileValid( argv[ 1 ] ))
	{
		cout << "Error. Invalid Configuration Data File Extension." << endl;
		return 0;
	} 

	

	return 0;
}



bool configFileValid( char string[] )
{
	int index = 0;
	while( string[ index ] != '\0')
	{
		if ( string[ index ] == '.' )
		{
			if( string[ index + 1 ] == 'c' &&
				string[ index + 2 ] == 'o' &&
				string[ index + 3 ] == 'n' &&
				string[ index + 4 ] == 'f' )

			{
				return true;
			}
		}
		index++;
	}
	return false;
}
