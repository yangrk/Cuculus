/*************************************************************
  Copyright (C), 2014
  File name: CuculusTimer.cpp
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

*************************************************************/


#include "CuculusTimer.h"
#include "ConfSock.h" 
#include "CuculusInc.h"



/************************************************************

  Function:  CuculusTimer:Init()
  Description:    
  Calls:         
  Called By:     
  Table Accessed: 
  Table Updated: 
  Input:  
        tSetTime:
	nSetInterval:
	pWork:
  Output:         
  Return:       
  Others:  

************************************************************/   
int CuculusTimer::Init( time_t &tSetTime, int nSetInterval, Work* pWork )
{
	m_stWorkTime = tSetTime;	
	m_nInterval = nSetInterval;
	m_pWork = pWork; 
}



/************************************************************
 
  Function:  CuculusTimer::operator()()
  Description:    
  Calls:         
  Called By:     
  Table Accessed: 
  Table Updated: 
  Input:  
        tSetTime:
        nSetInterval:
        pWork:
  Output:         
  Return:       
  Others:  

*************************************************************/ 

int CuculusTimer::operator()()
{
	TimerFunc();

}


/************************************************************

  Function:  CuculusTimer::TimerFunc()
  Description:    
  Calls:         
  Called By:     
  Table Accessed: 
  Table Updated: 
  Input:  
        tSetTime:
        nSetInterval:
        pWork:
  Output:         
  Return:       
  Others:  

*************************************************************/

void CuculusTimer::TimerFunc()
{
	boost::asio::io_service io;
	boost::asio::deadline_timer t(io);

	boost::posix_time::ptime tbaseTime  = boost::posix_time::from_time_t(m_stWorkTime);
	t.expires_at(tbaseTime);

	while(1)
	{
		t.wait();
		boost::posix_time::ptime expires = t.expires_at();

		long nTotalSeconds = expires.time_of_day().total_seconds();
		if( (nTotalSeconds % 60) == 59)
		{
			//定时器到点,

		}



		if( 0 != m_nInterval )
		{
			//如果 m_nInterval 被设置成0，则这个非周期性定时器
			tbaseTime +=boost::posix_time::milliseconds( m_nInterval  );
			t.expires_at(tbaseTime);
		}

	}

}




