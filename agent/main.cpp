/*************************************************************
  Copyright (C), 2014
  File name: main.cpp
  Author:yangrenke     Version : 1.0       Date:2014/12/3
  Description: 主函数
  Others:       
  Function List:
    History:
    <author>    <time>    <version >    <desc>
   yangrenke    2014/12/03     1.0     build this moudle 

**************************************************************/

#include <stdlib.h>
#include  "CuculusTimer.h"
#include "YearWork.h"
#include "CuculusInc.h"
#include "PublicStruct.h"

using namespace std;
using namespace plib;

JobItemHash  jobHash(1000);   

ShareBuffer<WorkTaskConfig *> yearJobBuf(1000);

void InitLog( IniFile & iniF );
int CreateJobHash( DBConfig & dbC );


int main( )
{

	// init ini file
	string strIniFilePath = "../INI/Cuculus.ini";

	IniFile ini;
	ini.LoadIniFile( strIniFilePath.c_str() );
	

	// init log
	InitLog( ini );
	Logger log;
        log.Info("main(): Cuculus server is running!");	


	//init DBBase Config
	DBConfig dbCon;
	dbCon.strServer = ini.GetString("DATABASE", "SERVER", "localhost");
        dbCon.strDB = ini.GetString("DATABASE", "DB", "");
        dbCon.strUser = ini.GetString("DATABASE", "USER", "");
        dbCon.strPassWord = ini.GetString("DATABASE", "PASSWORD", "");

	//create all the jobs' config from db ,and create hash table
	int nResult = CreateJobHash( dbCon );
	if( 0 != nResult )
	{
		log.Info("main(): there isn't any job!");
		return -1;
	}	


	boost::thread_group tg;

	// start the year work thread
	YearWork yWork;
	int nYR = yWork.Init( strIniFilePath );
	if( 0 == nYR )
	{
		//boost::thread yearthread( boost::ref(yWork) );
		tg.create_thread( boost::ref(yWork) );
	} 
	
	
	tg.join_all();


	/*
	time_t tYearTime;
        int nInterval = 3600;
	CuculusTimer  yearTime;
	int nR = yearTime.Init( tYearTime, nInterval, &yWork );
	if( 0 == nR )
	{
		boost::thread yearthread( boost::ref(yearTime) );
	}
	*/

	

	return 0;

}




void InitLog( IniFile & iniF )
{
        string strLogFile = iniF.GetString("CLOG","LOG_FILE","../Log/Cuculus");
        int nLogLevel = iniF.GetInteger("CLOG","LOG_LEVEL",9);
        int nLogType =iniF.GetInteger("CLOG","LOG_TYPE",1);

        string strPath = strLogFile;
        if(strPath.length() && strPath.at(strPath.length()-1)!='/')
        {
                strPath.append("/");
        }

        LogManager::CreateLongDirectory(strPath);
        LogManager::SetLogFilePath(strLogFile.c_str());
        LogManager::Open("Cuculus", nLogType);
        LogManager::SetLogLevel(nLogLevel);
}



int CreateJobHash( DBConfig & dbC )
{

	Logger log;
	// create the connection to mysql
	mysqlpp::Connection dbConnection;
	try
	{
        	bool bR = dbConnection.connect((dbC.strDB).c_str(),(dbC.strServer).c_str(),(dbC.strUser).c_str(),(dbC.strPassWord).c_str());
		if( !bR )
		{
			// fail to connect db
			 log.Error("CreateJobHash(): step1  connect to db failed!");
                        return -1;		

		}

	}
	catch(const mysqlpp::Exception& er)
        {
                log.Error("CreateJobHash(): step1  Error:%s[%d:%d]\n",(er.what()),__FILE__,__LINE__);
                return -1;
        }



	// get jobs' config from db 
	mysqlpp::Query query = dbConnection.query();
	try
        {
                string sql = std::string("select id,  name, location, parameter, task_type from tb_con_job_items");

                query<<sql;
                mysqlpp::StoreQueryResult res = query.store();

                WorkJobConfig ConfigSet;
                for (size_t i = 0; i < res.num_rows(); ++i)
                {
			ConfigSet.nId = res[i]["id"];
                        ConfigSet.strCommandName = (res[i]["name"]).c_str();
                        ConfigSet.strLocation = (res[i]["location"]).c_str();
                        ConfigSet.strParameter = (res[i]["parameter"]).c_str();
                        ConfigSet.nTaskType = res[i]["task_type"];
			jobHash.insert( map<int, WorkJobConfig>::value_type(ConfigSet.nId, ConfigSet) );                      

			query.clear();

                	log.Info("CreateJobHash(): get jobs' config from db success!");

		}

	}
	catch (const mysqlpp::ConnectionFailed& ce)
        {
		// Something went wrong with the db connection
		log.Error("CreateJobHash(): step2  Connection failed:%s[%d:%d]\n",(ce.what()),__FILE__,__LINE__);
                return -1;
	}
	catch (const mysqlpp::BadQuery& e)
        {	
		// Something went wrong with the SQL query
		log.Error("CreateJobHash(): step2  Query failed:%s[%d:%d]\n",(e.what()),__FILE__,__LINE__);
                return -1;
	}
	catch (const mysqlpp::Exception& er)
        {
		// Catch-all for any other MySQL++ exceptions
		log.Error("CreateJobHash() : step2  Error:%s[%d:%d]\n",(er.what()),__FILE__,__LINE__);
                return -1;

	}


        log.Info("CreateJobHash(): create job hashtable success!");


	return 0;
}


































