/**********************************************************
  Copyright (C), 2013-2014, JJMatch.
  File name: TaskThread.h
  Author:yangrenke    Version : 1.0       Date:2014/07/13 
  Description: TaskThread类定义
  Others:
       
  Function List:
        1.
        2.
      
  History:

    History:
      <author>  <time>   <version >   <desc>
      yangrenke   2014/07/13     1.0     build this moudle  

*************************************************************/



#ifndef TASK_THREAD_H
#define TASK_THREAD_H

#include <string>
#include "Logger.h"


using namespace plib;
using namespace std;

class TaskThread
{

public:
	TaskThread(){;};
	~TaskThread(){;};

	int Init( string );	
	int operator()();


private:

	string	a_strCommand;
	Logger      log;
	
};


#endif
