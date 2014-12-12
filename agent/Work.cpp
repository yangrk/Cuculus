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


/************************************************************
 
  Function:  Work::DoTask()
  Description:    
	启动任务
  Calls:         
  Called By:     
  Table Accessed: 
  Table Updated: 
  Input:  
  Output:         
  Return:       
  Others:  

*************************************************************/

int Work::DoTask( )
{
	string strHadoopPath =  m_serverPath.strHadoopPath;
        string strHivePath =  m_serverPath.strHivePath;

        if(strHadoopPath.length() && strHadoopPath.at(strHadoopPath.length()-1)!='/')
        {
                strHadoopPath.append("/");
        }

	if(strHivePath.length() && strHivePath.at(strHivePath.length()-1)!='/')
        {
                strHivePath.append("/");
        }


	for( int n=0; n<MAX_LEVEL; n++ )
        {
		int nSize = m_TaskConfigV[n].size();
                if( nSize = 0 )
                {
                        continue;
                }

		TaskThread pthNode[nSize];

                vector<WorkJobConfig>::iterator pNode = m_TaskConfigV[n].begin();
                boost::thread_group tg;

		for( int i=0 ; pNode != m_TaskConfigV[n].end(); pNode++, i++ )
                {
			char command[2000] = {0};
			if( 1 == pNode->nTaskType )
                        {
				// it's hadoop job
				if( (pNode->strParameter).empty())
                                {
                                        sprintf(command, "%shadoop jar %s/%s",strHadoopPath.c_str(),(pNode->strLocation).c_str(),(pNode->strCommandName).c_str());
                                        log.Debug("Work::DoTask(): it's hadoop job, the parameters of jar %s is null", (pNode->strCommandName).c_str());
                                }
                                else
                                {
                                        sprintf(command, "%shadoop  jar %s/%s %s", strHadoopPath.c_str(), (pNode->strLocation).c_str(), 
									(pNode->strCommandName).c_str(), (pNode->strParameter).c_str());
                                        log.Debug("Work::DoTask(): it's hadoop job, the parameters of jar %s is not null", (pNode->strCommandName).c_str());

                                }

			}
			else if(  2 == pNode->nTaskType )
			{
				// it's hive job
				if( (pNode->strParameter).empty() )
                                {
                                        sprintf(command, "%s/%s", (pNode->strLocation).c_str(), (pNode->strCommandName).c_str());
                                        log.Debug("Work::DoTask(): it's hive job, the parameters of jar %s is null", (pNode->strCommandName).c_str());
                                }
                                else
                                {
                                        sprintf(command, "%s/%s %s", (pNode->strLocation).c_str(), (pNode->strCommandName).c_str(), (pNode->strParameter).c_str());
                                        log.Debug("Work::DoTask(): it's hive job, the parameters of jar %s is not null", (pNode->strCommandName).c_str());

                                }

			}
	
			
			pthNode[i].Init( command );
                        tg.create_thread( boost::ref(pthNode[i]) );
		
		}//for

		tg.join_all();
		log.Info("Work::DoTask(): LeveL %d finished!",n);

	}

	return 0;

}



/************************************************************
 
  Function:  Work::SplitCommand()
  Description:    
    	分隔字符串
  Calls:         
  Called By:     
  Table Accessed: 
  Table Updated: 
  Input:  
        strCommand: 源字符串
	strDelimit: 分隔符字符串
	pVector: 结果向量
  Output:         
  Return:       
  Others:  

*************************************************************/
int  Work::SplitCommand(const string& srcCommand, string strDelimit, vector<string> *pVector )   
{    
	if( srcCommand.empty() || strDelimit.empty() )   
	{   
		return -1;   
	}
     
	basic_string<char>::size_type deliLen = strDelimit.size();  
	basic_string<char>::size_type nPos = -1;   
	long nIndex = nPos; 
	long nLastPosition = 0;     
	
	while( (nIndex=srcCommand.find(strDelimit, nLastPosition)) != nPos )    
	{     
		if( nIndex != nLastPosition )     
		{      
			pVector->push_back( srcCommand.substr(nLastPosition, nIndex-nLastPosition) );      
		}     
		
		nLastPosition = nIndex + deliLen;   
	 }      
	

	string strLastOne = srcCommand.substr(nLastPosition);
	if( !strLastOne.empty() ) 
	{    
		pVector->push_back( strLastOne );
	}

	return 0;
}


/************************************************************
  
  Function:  Work::GetJobConfig()
  Description:    
        根据任务链配置信息，从hash表中提取具体每个job的信息
  Calls:         
  Called By:     
  Table Accessed: 
  Table Updated: 
  Input:  
  Output:         
  Return:       
  Others:  

*************************************************************/
int Work::GetJobConfig()
{

	int nLevelCount = 1;
	for( int n=0; n<MAX_LEVEL; n++ )
        {
		nLevelCount++;
		
		int nSize = m_TaskChainV[n].size();
                if( nSize = 0 )
                {
                        continue;
                }

		plib::WorkJobConfig ConfigSet;
		vector<string>::iterator pNode = m_TaskChainV[n].begin();
		for( int i=0 ; pNode != m_TaskChainV[n].end(); pNode++, i++ )
                {
			JobItemHash::iterator pIter;
			int nId = std::atoi( pNode->c_str());	
			pIter = jobHash.find( nId );
			m_TaskConfigV[i].push_back( pIter->second );

		}
	}

	log.Info("Work::GetJobConfig: get job from hashtable success. total levels: %d\n", nLevelCount);
	return 0;
}




















