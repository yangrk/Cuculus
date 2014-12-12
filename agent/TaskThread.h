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
      yangrenke   2014/12/12     2.0     修改了Init接口，增加了两个数据域吗，用以记录改Job的ID和在任务链中的位置

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

	int Init( string, int, int );	
	int operator()();


private:

	string	m_strCommand;
	int  m_nJobId;//在数据库中的ID
	int m_nLevel;//在任务链中的位置
	Logger      log;
	
};


#endif
