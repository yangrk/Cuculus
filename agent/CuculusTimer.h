/*************************************************************
  Copyright (C), 2014
  File name: CuculusTimer.h
  Author:yangrenke     Version : 1.0       Date:2014/12/3 
  Description: 定时器类头文件
  Others:       
  Function List:
    1.CuculusTimer: 构造函数，初始化定时工作的时间以及间隔
    2.Run： 外部调用，启动定时器
    3.TimerFunc： 定时器的业务处理函数
  History:
    <author>    <time>    <version >    <desc>
   yangrenke    2014/12/03     1.0     build this moudle  

**************************************************************/


#ifndef C_TIMER_H
#define C_TIMER_H

#include <stdlib.h>
#include <time.h>
#include <ctime>
#include "Work.h"

using namespace std;

class CuculusTimer
{

public:
	CuculusTimer( ){;}
	int Init( time_t &, int, Work* );
	int operator()();

private:
	void TimerFunc();



private:
	time_t m_stWorkTime; //定时器启动时间
	int m_nInterval;//定时器间隔,单位是秒
	Work *m_pWork;//业务处理类


};





#endif


