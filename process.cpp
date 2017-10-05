// Program Information /////////////////////////////////////////////////////////
/**
  * @file process.cpp
  *
  * @brief implements PCB and process class   
  * 
  * @details defines member functions
  *
  * @version 1.00 Carli DeCapito
  *	  		 Original Document (10/4/17)
  *
  * @note None
  */
//precompiler directives
#ifndef PROCESS_CPP
#define PROCESS_CPP

//header files
#include "process.h"
#include <iostream>

using namespace std;


//PCB Implementation //////////////////////////////////////
/**
 * @brief constructor for PCB
 *
 * @details intializes PCB
 *          
 * @pre None
 *
 * @post None
 *
 * @par Algorithm 
 *      None
 *      
 * @exception None
 *
 * @param [in] none
 *
 * @param [out] none
 *
 * @return None
 *
 * @note None
 */
PCB::PCB()
{
	//nothing
}


/**
 * @brief destructor
 *
 * @details resets PCB members
 *          
 * @pre None
 *
 * @post None
 *
 * @par Algorithm 
 *      None
 *      
 * @exception None
 *
 * @param [in] None
 *
 * @param [out] None
 *
 * @return None
 *
 * @note None
 */
 
PCB::~PCB()
{
	//nothing
}

/**
 * @brief setState
 *
 * @details sets new state
 *          
 * @pre none
 *
 * @post state is assigned
 *
 * @par Algorithm 
 *      None
 *      
 * @exception None
 *
 * @param [in] newState provides int value of new state
 *
 * @param [out] None
 *
 * @return None
 *
 * @note None
 */

void PCB::setState( int newState )
{
	state = newState;
}


//process implementation///////////////////////////////////
/**
 * @brief constructor
 *
 * @details initalizes process
 *          
 * @pre None
 *
 * @post state is set to ready
 *
 * @par Algorithm 
 *      function call
 *      
 * @exception None
 *
 * @param [in] None
 *
 * @param [out] None
 *
 * @return None
 *
 * @note None
 */
process::process()
{
	pcb.setState( 0 );
}

/**
 * @brief destructor
 *
 * @details resets pcb to terminate
 *          
 * @pre none
 *
 * @post pcb state is set to terminate
 *
 * @par Algorithm 
 *      Function call
 *      
 * @exception None
 *
 * @param [in] None
 *
 * @param [out] None
 *
 * @return None
 *
 * @note None
 */
 
process::~process()
{
	pcb.setState( 4 );
}


/**
 * @brief changeState
 *
 * @details assigns pcb state to state
 *          
 * @pre none
 *
 * @post pcb state is set to state 
 *
 * @par Algorithm 
 *      function call
 *      
 * @exception None
 *
 * @param [in] state provides int value of new state
 *
 * @param [out] None
 *
 * @return None
 *
 * @note None
 */
void process::changeState( int state )
{
	pcb.setState( state );
}


#endif