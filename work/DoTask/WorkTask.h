/***********************************************************
  Copyright (C), 2013, JJMatch
  File name: HadoopTask.h
  Author:yangrenke    Version : 1.0       Date:2013/08/22 
  Description: HadoopTask's head file 
  Others:
       
  Function List:
        1.operator()() the master function, thread will start from this point
        2.Init(int nTaskType): init the task type and  init the db connection
	3.GetConfig(): get configuration data from db
	4.DoTask(): run the hadoop jobs
      
  History:
      <author>	<time>		<version >   	<desc>
      yangrenke   2013/08/22     1.0     	build this moudle  
************************************************************/


#ifndef HADOOP_TASK_H
#define HADOOP_TASK_H

#include <string.h>
#include <vector>

#include <mysql++.h>


#include "PublicStruct.h"
#include "Logger.h"

#define MAX_LEVEL 9

using namespace std;
using namespace plib;

class WorkTask
{
public:
	WorkTask() {;}
	~WorkTask() {;}

	int operator()();
	int Init(string strTimeType, ServerPath &spPath, DBConfig *);
	
private:

	int GetConfig();
	int DoTask();



private:

	string a_strTimeType; // the type of task
	string a_strHadoopPath; // the hadoop's install path
	string a_strHivePath; // the hive's install path
	vector<WorkTaskConfig> TaskConfigVc[MAX_LEVEL];
	
	mysqlpp::Connection *a_pDB;
	Logger      log;

};
#endif

