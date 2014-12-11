/*****************************************************************
  Copyright (C), 2013  JJMatch
  File name: TaskThread.cpp
  Author:yangrenke    Version : 1.0       Date:2014/07/13
  Description:  
  History:
  <author>      <time>          <version>       <desc>
  yangrenke     2014/07/13      1.0             build this moudle
******************************************************************/


#include <stdlib.h>
#include "TaskThread.h"



/************************************************************
  Function:  TaskTread::Init()
  Description:    
        initing the command string
  Calls:         
  Called By:     
  Table Accessed: 
  Table Updated: 
  Input:  
        string  strComand:  the string of command
  Output:         
  Return:       
  Others:        
*************************************************************/ 

int  TaskThread::Init( string strCommand )
{
	a_strCommand = strCommand;
}



/************************************************************
  Function:  TaskThread::operator()()
  Description:    
        the master function
  Calls:         
  Called By:     
  Table Accessed: 
  Table Updated: 
  Input:  
  Output:         
  Return:       
  Others:        
*************************************************************/

int  TaskThread::operator()()
{

	system( a_strCommand.c_str() );
	log.Info("TaskThread::operator(): Task  [%s]  finished!", a_strCommand.c_str());

}





