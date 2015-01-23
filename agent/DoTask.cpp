/*************************************************************
  Copyright (C), 2014
  File name: DoTask.cpp
  Author:yangrenke     Version : 1.0       Date:2015/01/14
  Description:
  Others:       
  Function List:
    History:
    <author>    <time>    <version >    <desc>
   yangrenke    2015/01/14     1.0     build this moudle 
**************************************************************/


#include <stdlib.h>
#include "CuculusInc.h"
#include "DoTask.h"
#include "TaskThread.h"

using namespace boost;


extern JobItemHash jobHash;
extern ShareBuffer<WorkTaskConfig *> yearJobBuf;
extern hash_set<int> HashSetYearTaskID;



int DoTask::Init( WorkTaskConfig *pWTC, string strHadoopPath )
{
	if( NULL == pWTC )
	{
		return -1;
	}

	m_pWTC = pWTC;

	m_strHadoopPath = strHadoopPath;

	return 0;
}




int DoTask::SplitCommand( const string& srcCommand, string strDelimit, vector<string> *pVector )
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




int DoTask::GetJobConfig()
{
	int nLevelCount = 1;
	for( int n=0; n<MAX_LEVEL; n++ )
	{

		int nSize = m_TaskChainV[n].size();
		if( 0 == nSize )
		{
			continue;
		}
		else
		{
			nLevelCount++;
		}

		plib::WorkJobConfig ConfigSet;
		vector<string>::iterator pNode = m_TaskChainV[n].begin();
		for( ; pNode != m_TaskChainV[n].end(); pNode++ )
		{
			JobItemHash::iterator pIter;
			int nId = std::atoi( pNode->c_str());	
			pIter = jobHash.find( nId );

			m_TaskConfigV[n].push_back( pIter->second );

		}

		printf("m_TaskConfigV[%d] size:%d\n", n, m_TaskConfigV[n].size());
	}

	log.Info("DoTask::GetJobConfig: get job from hashtable success. total levels: %d\n", nLevelCount);
	return 0;

}



int DoTask::DoJob()
{

       if(m_strHadoopPath.length() && m_strHadoopPath.at(m_strHadoopPath.length()-1)!='/')
        {
                m_strHadoopPath.append("/");
        }



	for( int n=0; n<MAX_LEVEL; n++ )
        {
		int nSize = m_TaskConfigV[n].size();
                if( 0 == nSize )
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
                                        sprintf(command, "%shadoop jar %s/%s",m_strHadoopPath.c_str(),(pNode->strLocation).c_str(),(pNode->strCommandName).c_str());
                                        log.Debug("DoTask::DoJob(): it's hadoop job, the parameters of jar %s is null", (pNode->strCommandName).c_str());
                                }
                                else
                                {
                                        sprintf(command, "%shadoop  jar %s/%s %s", m_strHadoopPath.c_str(), (pNode->strLocation).c_str(), 
									(pNode->strCommandName).c_str(), (pNode->strParameter).c_str());
                                        log.Debug("DoTask::DoJob(): it's hadoop job, the parameters of jar %s is not null", (pNode->strCommandName).c_str());

                                }

			}else if( 2 == pNode->nTaskType )
			{
				// it's hive job
				if( (pNode->strParameter).empty() )
                                {
                                        sprintf(command, "%s/%s", (pNode->strLocation).c_str(), (pNode->strCommandName).c_str());
                                        log.Debug("DoTask::DoJob(): it's hive job, the parameters of jar %s is null", (pNode->strCommandName).c_str());
                                }
                                else
                                {
                                        sprintf(command, "%s/%s %s", (pNode->strLocation).c_str(), (pNode->strCommandName).c_str(), (pNode->strParameter).c_str());
                                        log.Debug("DoTask::DoJob(): it's hive job, the parameters of jar %s is not null", (pNode->strCommandName).c_str());

                                }
			}

			pthNode[i].Init( command, pNode->nId, n );
                        tg.create_thread( boost::ref(pthNode[i]) );		

		}//for( int i=0 ; pNode != m_TaskConfigV[n].end(); pNode++, i++ )	

		tg.join_all();
		log.Info("DoTask::DoJob(): LeveL %d finished!",n+1);		

	}//for( int n=0; n<MAX_LEVEL; n++ )

	return 0;
}


int DoTask::operator()( )
{

	//解析任务链
	vector<string> vLevelCommand;

	int nResult = SplitCommand( m_pWTC->strTaskChain, ";", &vLevelCommand );

	if( 0 == nResult  )
	{
		for( int i=0; i<vLevelCommand.size(); i++ )
		{
			SplitCommand( vLevelCommand[i], ",", &m_TaskChainV[i] );

			printf(" m_TaskChainV[%d] size: %d\n", i, m_TaskChainV[i].size());
		}
	}


	//从哈希表中获取任务链中的任务的配置信息
	GetJobConfig();

	//清理内存
	//delete m_pWTC;
	//m_pWTC = NULL;

	//执行任务
	DoJob();

	log.Info("DoTask::operator()(): operator() finished!");
        
	return 0;

}


















