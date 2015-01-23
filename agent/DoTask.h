/*************************************************************
  Copyright (C), 2014
  File name: DoTask.h
  Author:yangrenke     Version : 1.0       Date:2015/01/14 
  Description: 定时器执行任务
  Others:       
  Function List:
  
  History:
    <author>    <time>    <version >    <desc>
   yangrenke    2015/01/14     1.0     build this moudle  
*************************************************************/

#ifndef DO_TASK_H
#define DO_TASK_H

#include <string.h>
#include <vector>



#include "PublicStruct.h"
#include "Logger.h"
#include "ShareCycqueue.h"

//#define MAX_LEVEL 9


using namespace std;
using namespace plib;

class DoTask
{
public:

	DoTask(){;}
	~DoTask(){;}

	int operator()();
	int Init(WorkTaskConfig *, string);

private:
	
	int SplitCommand(const string&, string, vector<string> *);
        int GetJobConfig();
	int DoJob();

private:
	WorkTaskConfig *m_pWTC;	
	string m_strHadoopPath;
	
	vector<WorkJobConfig> m_TaskConfigV[MAX_LEVEL];
        vector<string> m_TaskChainV[MAX_LEVEL];
        Logger log;

};
#endif





















