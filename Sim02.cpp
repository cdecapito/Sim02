
//header files
#include <iostream>
#include <vector>
#include "data.h"
#include "process.h"
#include "readData.cpp"
#include "simFuncs.cpp"

using namespace std;

//main driver functions
bool configFileValid( char string[] );

//main driver implmentation
int main( int argc, char* argv[] )
{
	configData cdata;
	vector<metaData> mdata;
	vector<process> pdata;
	
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

	if ( !getConfigData( argv[1], cdata ) )
	{
		return 0;
	}

	if( !getMetaData( cdata.filePath, mdata ) )
	{
		return 0;
	}

	//split data into processes
	splitMetaData( pdata, mdata );

	//output data to file and/or monitor
	logData( cdata, pdata );

	return 0;
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
