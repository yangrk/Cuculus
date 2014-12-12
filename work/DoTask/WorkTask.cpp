/*************************************************************
  Copyright (C), 2013  JJMatch
  File name: HadoopTask.cpp
  Author:yangrenke    Version : 1.0       Date:2013/08/22
  Description:  
  History:
  <author>	<time>   	<version>   	<desc>
  yangrenke	2013/08/22     	1.0     	build this moudle  
**************************************************************/


#include "WorkTask.h"
#include "TaskThread.h"

#include <boost/thread.hpp>
#include <boost/bind.hpp>

using namespace boost;


/************************************************************
  Function:  WorkTask::Init()
  Description:    
	initing the db, and task type
  Calls:         
  Called By:     
  Table Accessed: 
  Table Updated: 
  Input:  
	int  nTaskType:  the type of task 
  Output:         
  Return:       
  Others:        
*************************************************************/

int WorkTask::Init( string strTimeType, ServerPath &spPath, DBConfig *pDB)
{
	if( NULL == pDB )
	{
		return -1;
	}


	// create the connection to mysql
	try
	{
		a_pDB = new mysqlpp::Connection();
		bool bR =  a_pDB->connect((pDB->strDB).c_str(), (pDB->strServer).c_str(), (pDB->strUser).c_str(), (pDB->strPassWord).c_str());

		if( !bR )
		{
			// fail to connect db
			cout<<"error:"<<a_pDB->error()<<endl;
			log.Error("WorkTask::Init(): connect to db failed!");
			return -1;
		}
	}
	catch(const mysqlpp::Exception& er)
	{
		log.Error("WorkTask::Init(): Error:%s[%d:%d]\n",(er.what()),__FILE__,__LINE__);
		return -1;	
	}


	// set the task type
	a_strTimeType = strTimeType;

	// set the hadoop's install path
	a_strHadoopPath = spPath.strHadoopPath;
	a_strHivePath = spPath.strHivePath;
	
	log.Debug("WorkTask::Init(): a_strTimeType:%s, a_strHadoopPath:%S ", a_strTimeType.c_str(), a_strHadoopPath.c_str());

	log.Info("WorkTask::Init(): init success!");
	return 0;
}



/************************************************************
  Function:  WorkTask::operator()()
  Description:    
        the master function
  Calls:         
  Called By:     
  Table Accessed: 
  Table Updated: 
  Input:  
  Output:         
  Return:       
  Others:        
*************************************************************/
int  WorkTask::operator()()
{
	GetConfig();
	DoTask();


	log.Info("WorkTask::operator()(): operator() finished!");
	return 0;
}


/************************************************************
  Function:  WorkTask::GetConfig()
  Description:   
	get all the configuration from db, then initing the class 
  Calls:         
  Called By:
	WorkTask::operator()()     
  Table Accessed: 
	tb_con_mr_hour
  Table Updated: 
  Input:  
  Output:         
  Return:       
  Others:        
*************************************************************/
int WorkTask::GetConfig()
{

	//get data from db
	try
	{
		mysqlpp::Query query = a_pDB->query();
		string sql;
		if( "Hour" == a_strTimeType )
       		{ 
       			sql = std::string("select name, location, parameter, state, task_type, level_type from tb_con_work_hour");
		}else if( "Day" == a_strTimeType )
		{
			sql = std::string("select name, location, parameter, state, task_type, level_type from tb_con_work_day");
		}else if( "Week" == a_strTimeType )
                {
			sql = std::string("select name, location, parameter, state, task_type, level_type from tb_con_work_week");
		} 
                else if( "Month" == a_strTimeType )
                {
			sql = std::string("select name, location, parameter, state, task_type, level_type from tb_con_work_month");
                }		
                else if( "Year" == a_strTimeType )
             	{
			sql = std::string("select name, location, parameter, state, task_type, level_type from tb_con_work_year");
		}
		else 
		{
			sql = std::string("select name, location, parameter, state, task_type, level_type from tb_con_work_other");
		}
		
		query<<sql;
		mysqlpp::StoreQueryResult res = query.store();

		plib::WorkTaskConfig ConfigSet;
		for (size_t i = 0; i < res.num_rows(); ++i)
		{	
			ConfigSet.strCommandName = (res[i]["name"]).c_str();
			ConfigSet.strLocation = (res[i]["location"]).c_str();
			ConfigSet.strParameter = (res[i]["parameter"]).c_str();
			ConfigSet.nTaskType = res[i]["task_type"];
			ConfigSet.nLevelType= res[i]["level_type"];
			TaskConfigVc[ConfigSet.nLevelType].push_back( ConfigSet );
		}

		query.clear();

		log.Info("WorkTask::GetConfig(): get config data from db success!");
		
	}catch (const mysqlpp::ConnectionFailed& ce)
	{
		// Something went wrong with the db connection
		log.Error("WorkTask::GetConfig():Connection failed:%s[%d:%d]\n",(ce.what()),__FILE__,__LINE__);
		return -1;
	}
	catch (const mysqlpp::BadQuery& e)	
	{
		// Something went wrong with the SQL query
		log.Error("WorkTask::GetConfig(): Query failed:%s[%d:%d]\n",(e.what()),__FILE__,__LINE__);
		return -1;
	}
	catch (const mysqlpp::Exception& er)
	{
		// Catch-all for any other MySQL++ exceptions
		log.Error("WorkTask::GetConfig(): Error:%s[%d:%d]\n",(er.what()),__FILE__,__LINE__);
		return -1;
	}




	return 0;

}







/************************************************************
  Function:  WorkTask::DoTask()
  Description:   
  Calls:         
  Called By:
  WorkTask::operator()()     
  Table Accessed: 
  Table Updated: 
  Input:  
  Output:         
  Return:       
  Others:        
*************************************************************/
int  WorkTask::DoTask()
{

	string strHadoopPath = a_strHadoopPath;
	string strHivePath = a_strHivePath;
	
	if(strHadoopPath.length() && strHadoopPath.at(strHadoopPath.length()-1)!='/')
	{
		strHadoopPath.append("/");
	}
	


        for( int n=1; n<MAX_LEVEL; n++ )
        {
		int nSize = TaskConfigVc[n].size();
		if( nSize = 0 )
		{
			continue;
		}


		TaskThread pthNode[nSize];

		vector<WorkTaskConfig>::iterator pNode = TaskConfigVc[n].begin();
		boost::thread_group tg;
		for( int i=0 ; pNode != TaskConfigVc[n].end(); pNode++, i++ )
		{
			char command[2000] = {0};

			if( 1 == pNode->nTaskType )
			{
				// it's hadoop job
				if( (pNode->strParameter).empty())
				{
					sprintf(command, "%shadoop  jar %s/%s",strHadoopPath.c_str(), (pNode->strLocation).c_str(), (pNode->strCommandName).c_str());
					log.Debug("WorkTask::DoTask(): it's hadoop job, the parameters of jar %s is null", (pNode->strCommandName).c_str()); 
				}
				else
				{
					sprintf(command, "%shadoop  jar %s/%s %s",
					   strHadoopPath.c_str(), (pNode->strLocation).c_str(), (pNode->strCommandName).c_str(), (pNode->strParameter).c_str());

					log.Debug("WorkTask::DoTask(): it's hadoop job, the parameters of jar %s is not null", (pNode->strCommandName).c_str());

				}		
			}
			else if(  2 == pNode->nTaskType )
			{
				// it's hive job
				if( (pNode->strParameter).empty() )
				{
					sprintf(command, "%s/%s", (pNode->strLocation).c_str(), (pNode->strCommandName).c_str());
					log.Debug("WorkTask::DoTask(): it's hive job, the parameters of jar %s is null", (pNode->strCommandName).c_str()); 
				}
				else
				{
					sprintf(command, "%s/%s %s", (pNode->strLocation).c_str(), (pNode->strCommandName).c_str(), (pNode->strParameter).c_str());
					log.Debug("WorkTask::DoTask(): it's hive job, the parameters of jar %s is not null", (pNode->strCommandName).c_str());

				}

			}

			//system( command );

			pthNode[i].Init( command );
			tg.create_thread( boost::ref(pthNode[i]) );
			//tg1.create_thread(bind(&system, command));

		}//for

		tg.join_all();
		log.Info("WorkTask::DoTask(): LeveL %d finished!",n);

	}

	log.Info("WorkTask::DoTask(): DoTask finished!");


	return 0;

}













