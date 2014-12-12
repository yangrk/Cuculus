/*****************************************************************
  Copyright (C), 2013  JJMatch
  File name: TaskThread.cpp
  Author:yangrenke    Version : 1.0       Date:2014/07/13
  Description:  
  History:
  <author>       <time>       <version>     <desc>
  yangrenke     2014/07/13      1.0       build this moudle
  yangrenke     2014/12/12      2.0       修改了Init接口，增加了两个数据域吗，用以记录改Job的ID和在任务链中的位置

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

int  TaskThread::Init( string strCommand, int nId, int nLevel )
{

	m_strCommand = strCommand;
	m_nJobId = nId;
	m_nLevel = nLevel;
	
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

	int nR = system( m_strCommand.c_str() );
	if( nR < 0 )
	{
		//错误处理
		


	}

	log.Info("TaskThread::operator(): Task  [%s]  finished!", m_strCommand.c_str());

	return 0;
}





