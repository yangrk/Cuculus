/*************************************************************
  Copyright (C), 2014
  File name: Work.cpp
  Author:yangrenke     Version : 1.0       Date:2014/12/3 
  Description: 业务处理基类实现文件
  Others:       
  Function List:
    1.CuculusTimer: 构造函数，初始化定时工作的时间以及间隔
    2.Run： 外部调用，启动定时器
    3.TimerFunc： 定时器的业务处理函数
  History:
    <author>    <time>    <version >    <desc>
   yangrenke    2014/12/03     1.0     build this moudle 
 
**************************************************************/


#include <stdlib.h>
#include "Work.h"

#include "TaskThread.h"

#include <boost/thread.hpp>
#include <boost/bind.hpp>

using namespace boost;

extern JobItemHash  jobHash;


/************************************************************
 
  Function:  Work::Init()
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

*************************************************************/


int Work::Init( string strIniFilePath )
{
	return 0;
}


/************************************************************
  
  Function:  Work::InitIni()
  Description:    
	初始化配置文件路径
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

void Work::InitIni( string &strIniFilePath )
{
	 m_ini.LoadIniFile( strIniFilePath.c_str() );
}




/************************************************************
  Function:  Work::InitPath()
  Description:    
	初始化框架组件路径
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

void Work::InitPath()
{
	
	string strHadoopPath = m_ini.GetString("TASK", "HADOOP_PATH", "/usr/local/hadoop/bin");
        string strHivePath = m_ini.GetString("TASK", "HIVE_PATH", "/usr/local/hive/bin");

	m_serverPath.strHadoopPath = strHadoopPath;
        m_serverPath.strHivePath = strHivePath;

}






/************************************************************
  Function:  Work::InitDBConnection()
  Description:    
	初始化数据库连接
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

int Work::InitDBConnection()
{
	
	// get DB config
	m_dbC.strServer = m_ini.GetString("DATABASE", "SERVER", "localhost");
        m_dbC.strDB = m_ini.GetString("DATABASE", "DB", "");
        m_dbC.strUser = m_ini.GetString("DATABASE", "USER", "");
        m_dbC.strPassWord = m_ini.GetString("DATABASE", "PASSWORD", "");


	// create the connection to mysql
	try
	{
		m_pDB = new mysqlpp::Connection();
                bool bR =  m_pDB->connect( (m_dbC.strDB).c_str(), (m_dbC.strServer).c_str(), (m_dbC.strUser).c_str(), (m_dbC.strPassWord).c_str());

                if( !bR )
                {
                	// fail to connect db
                        cout<<"error:"<<m_pDB->error()<<endl;
                        log.Error("Work::InitDBConnection(): connect to db failed!");
                       	return -1;
              	}	
		
	}
	catch(const mysqlpp::Exception& er)
	{
		log.Error("Work::InitDBConnection(): Error:%s[%d:%d]\n",(er.what()),__FILE__,__LINE__);
                return -1;
	}

	log.Info("Work::InitDBConnection(): init success!");

	return 0;
}

















