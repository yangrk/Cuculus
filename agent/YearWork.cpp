/*************************************************************
 
  Copyright (C), 2014
  File name: YearWork.cpp
  Author:yangrenke     Version : 1.0       Date:2014/12/5
  Description: 业务处理基类实现文件
  Others:       
  Function List:
    1.CuculusTimer: 构造函数，初始化定时工作的时间以及间隔
    2.Run： 外部调用，启动定时器
    3.TimerFunc： 定时器的业务处理函数
  History:
    <author>    <time>    <version >    <desc>
   yangrenke    2014/12/05     1.0     build this moudle 
   yangrenke    2014/12/05     1.1     add the HashSetYearTaskID

*************************************************************/


#include <stdlib.h>
#include "YearWork.h"
#include "CuculusInc.h"
#include "DoTask.h"

using namespace boost;
using namespace plib;

extern JobItemHash jobHash;

extern ShareBuffer<WorkTaskConfig *> yearJobBuf;
extern hash_set<int> HashSetYearTaskID;

/************************************************************
  
  Function:  YearWork::Init()
  Description:    
  Calls:         
  Called By:     
  Table Accessed: 
  Table Updated: 
  Input:  
        strIniFilePath: 配置文件的路径
  Output:         
  Return:       
  Others:  

************************************************************/
int YearWork::Init( string strIniFilePath )
{
	// init the ini file
	InitIni( strIniFilePath );

	//init the path
	InitPath( );

	// init log
	InitLog();

	//init db
	int nR = InitDBConnection();
        if( -1 == nR )
        {
		log.Info("YearWork::Init(): init failed!");
		return -1;
        }

        log.Info("YearWork::Init(): init success!");
        return 0;

}



/************************************************************
  Function:  YearWork::InitLog()
  Description:    
	初始化Log配置
  Calls:         
  Called By:     
  Table Accessed: 
  Table Updated: 
  Input:  
  Output:         
  Return:       
  Others:  

************************************************************/
int YearWork::InitLog()
{
	/*
	string strLogFile = m_ini.GetString("YEARLOG","LOG_FILE","../Log/Year");
        int nLogLevel = m_ini.GetInteger("YEARLOG","LOG_LEVEL",9);
        int nLogType = m_ini.GetInteger("YEARLOG","LOG_TYPE",1);

        string strPath = strLogFile;
        if(strPath.length() && strPath.at(strPath.length()-1)!='/')
        {
                strPath.append("/");
        }

        LogManager::CreateLongDirectory(strPath);
        LogManager::SetLogFilePath(strLogFile.c_str());
        LogManager::Open("YearWork", nLogType);
        LogManager::SetLogLevel(nLogLevel);
	*/

        log.Info("YearWork::Init():service YearWork is running!");
	

	return 0;
}


/************************************************************

  Function:  YearWork::GetTaskConfig()
  Description:    
	从数据库表中获取任务链的配置信息，结果存放在yearJobBuf全局共享缓存里面。
  Calls:         
  Called By:     
  Table Accessed: 
  Table Updated: 
  Input:  
  Output:         
  Return:       
  Others:  

************************************************************/
int YearWork::GetTaskConfig()
{
	try
        {
       		mysqlpp::Query query = m_pDB->query();
     		string sql = std::string("select id,  execute_time, task_chain from tb_con_task_year");

		query<<sql;
                mysqlpp::StoreQueryResult res = query.store();

                for (size_t i = 0; i < res.num_rows(); ++i)
                {
			WorkTaskConfig *pConfigSet = new WorkTaskConfig();		

			pConfigSet->nId = res[i]["id"];
                        pConfigSet->strExecuteTime = (res[i]["execute_time"]).c_str();
                        pConfigSet->strTaskChain = (res[i]["task_chain"]).c_str();
                        
			//将任务链插入处理队列
			yearJobBuf.producer( pConfigSet );
			
			//将任务链ID插入到hash_set中
			HashSetYearTaskID.insert( pConfigSet->nId );                        

                }

                query.clear();


		log.Info("YearWork::GetConfig(): get config data from db success!");
	

	}
	catch (const mysqlpp::ConnectionFailed& ce)
	{
		// Something went wrong with the db connection
		log.Error("YearWork::GetConfig():Connection failed:%s[%d:%d]\n",(ce.what()),__FILE__,__LINE__);
                return -1;
	}
	catch (const mysqlpp::BadQuery& e)
	{	
		// Something went wrong with the SQL query
		log.Error("YearWork::GetConfig(): Query failed:%s[%d:%d]\n",(e.what()),__FILE__,__LINE__);
                return -1;
	}
	catch (const mysqlpp::Exception& er)
	{
		// Catch-all for any other MySQL++ exceptions
		log.Error("YearWork::GetConfig(): Error:%s[%d:%d]\n",(er.what()),__FILE__,__LINE__);
                return -1;
	}



	return 0;
}


/************************************************************
  
  Function:  YearWork::TimerFunc()
  Description:    
	定时器函数,控制定时
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
int YearWork::TimerFunc( struct tm &tSetTime, WorkTaskConfig *pWTC, string strPath )
{
	
	int nTaskID = pWTC->nId;
	string strHadoopPath = strPath;	


	time_t tNow;
	tNow = time(NULL);

	time_t tSet = mktime(&tSetTime);

	long nInterval = difftime( tSet, tNow );

	if( nInterval < 0 )
	{
		// 此时，今年已经过了设定的时间点，从明年开始
		tSetTime.tm_year = tSetTime.tm_year+1;
		time_t tSetNew = mktime(&tSetTime);
                nInterval = difftime( tSetNew, tNow );
        }

	boost::asio::io_service io;
        boost::asio::deadline_timer tDeadTimer(io);

        boost::posix_time::ptime tBaseTime  = boost::posix_time::from_time_t( std::time(NULL) );
	tBaseTime += boost::posix_time::seconds(nInterval);
	tDeadTimer.expires_at(tBaseTime);

	log.Debug(" YearWork::TimerFunc(): Timer Starts!,[year=%d,month=%d,day=%d,hour=%d,min=%d,sec=%d]",tSetTime.tm_year,tSetTime.tm_mon,tSetTime.tm_mday,tSetTime.tm_hour,tSetTime.tm_min,tSetTime.tm_sec);

	while(1)
        {
                tDeadTimer.wait();
		
		hash_set<int>::iterator pos;  
		pos = HashSetYearTaskID.find( nTaskID );
		if (pos == HashSetYearTaskID.end()) 
		{
			//该任务已经被删除
			break;
		}


                boost::posix_time::ptime expires = tDeadTimer.expires_at();

                long nTotalSeconds = expires.time_of_day().total_seconds();
		long nTotalMill = expires.time_of_day().total_milliseconds();
        
	
         	//定时器到点
		DoTask doT;
		int nResult = doT.Init( pWTC, strHadoopPath );
		if( 0 == nResult )
		{
			boost::thread tDoTask( boost::ref(doT) );
			tDoTask.join();
			
		}
		else
		{
			log.Error("YearWork::TimeFunc(): Init DoTask Thread failed !");
		}
		

		//计算到下次的间隔时间
		time_t tN;
                tN = time(NULL);
                //tSetTime.tm_year = tSetTime.tm_year+1;
		tSetTime.tm_min = tSetTime.tm_min + 2;
		time_t tNextSet = mktime( &tSetTime );
                long nI = difftime( tNextSet, tN );
                tBaseTime += boost::posix_time::seconds(nI);
                tDeadTimer.expires_at(tBaseTime);

		log.Debug("YearWork::TimerFunc():The next time is:[year=%d,month=%d,day=%d,hour=%d,min=%d,sec=%d]",tSetTime.tm_year,tSetTime.tm_mon,tSetTime.tm_mday,tSetTime.tm_hour,tSetTime.tm_min,tSetTime.tm_sec);
						

	}
        
	delete pWTC;
	pWTC = NULL;
	
	return 0;

}



/************************************************************
  
  Function:  YearWork::operator()()
  Description:    
  Calls:         
  Called By:     
  Table Accessed: 
  Table Updated: 
  Input:  
  Output:         
  Return:       
  Others:  

************************************************************/
int  YearWork::operator()()
{
        GetTaskConfig();

	while( true )
	{
		WorkTaskConfig *pWTC = yearJobBuf.consumer();	
        	
		WorkTaskConfig *pWTCNew = new WorkTaskConfig();
		pWTCNew->nId = pWTC->nId;
		pWTCNew->strExecuteTime.assign(pWTC->strExecuteTime);
		pWTCNew->strTaskChain.assign(pWTC->strTaskChain);

		//启动定时器服务

		string strMon = (pWTC->strExecuteTime).substr(0,2);
		string strDay = (pWTC->strExecuteTime).substr(2,2);
		string strHour = (pWTC->strExecuteTime).substr(4,2);
		string strMin = (pWTC->strExecuteTime).substr(6,2);
		string strSec = (pWTC->strExecuteTime).substr(8);		

		struct tm tmSetTime;
		time_t tNow;
        	tNow = time(NULL);
		struct tm *ptmNow = localtime(&tNow);
		tmSetTime.tm_year = ptmNow->tm_year;
		tmSetTime.tm_mon = std::atoi( strMon.c_str() ) - 1;
		tmSetTime.tm_mday = std::atoi( strDay.c_str() );
		tmSetTime.tm_hour = std::atoi( strHour.c_str() );
		tmSetTime.tm_min = std::atoi( strMin.c_str() );
		tmSetTime.tm_sec = std::atoi( strSec.c_str() );

		boost::function<int (struct tm, WorkTaskConfig *, string)> memberFunctionWrapper(boost::bind(&YearWork::TimerFunc, this, _1,_2,_3));
		boost::thread tTimeServer(boost::bind(memberFunctionWrapper, tmSetTime, pWTCNew,m_serverPath.strHadoopPath));

		delete pWTC;
		pWTC = NULL;

	}


        log.Info("YearWork::operator()(): operator() finished!");
        return 0;
}











