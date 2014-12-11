/*************************************************************
  Copyright (C), 2014
  File name: work.h
  Author:yangrenke     Version : 1.0       Date:2014/12/3 
  Description: 业务处理基类头文件
  Others:       
  Function List:
    1.CuculusTimer: 构造函数，初始化定时工作的时间以及间隔
    2.Run： 外部调用，启动定时器
    3.TimerFunc： 定时器的业务处理函数
  History:
    <author>    <time>    <version >    <desc>
   yangrenke    2014/12/03     1.0     build this moudle  

**************************************************************/


#ifndef WORK_H
#define WORK_H

#include <string.h>
#include <vector>
#include <mysql++.h>


#include "PublicStruct.h"
#include "IniFile.h"
#include "Logger.h"
#include "ShareCycqueue.h"

#define MAX_LEVEL 9


using namespace std;
using namespace plib;

class Work
{
public:
	Work(){;}
	virtual ~Work(){;} 

	virtual int operator()()=0;
	virtual int Init( string  );


protected:
	void InitPath();
	void InitIni( string & );
	int InitDBConnection();
	int SplitCommand(const string&, string, vector<string> *);
	int GetJobConfig();

	virtual int InitLog()=0;
	virtual int GetTaskConfig()=0;
	virtual int TimerFunc( struct tm & )=0;
	int DoTask( );
	
	
protected:

	IniFile m_ini;
	DBConfig m_dbC;
	ServerPath m_serverPath;
	mysqlpp::Connection *m_pDB;	

	vector<WorkJobConfig> m_TaskConfigV[MAX_LEVEL];
	vector<string> m_TaskChainV[MAX_LEVEL];
	Logger log;

};




#endif

