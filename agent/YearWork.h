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

#ifndef YEAR_WORK_H
#define YEAR_WORK_H

#include "Work.h"

using namespace std;

class YearWork:public Work
{
public:
	YearWork(){;}
	~YearWork(){;}

	int Init( string );
	int operator()();

private:
	virtual int InitLog();
	int TimerFunc( struct tm &, WorkTaskConfig *, string );
	int GetTaskConfig();

private:
	Logger Log;

};


#endif
