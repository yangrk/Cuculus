/**************************************************************
  Copyright (C), 2013  JJMatch
  File name: main.cpp
  Author:yangrenke    Version : 1.0       Date:2013/08/22
  Description:  
  History:
  <author>      <time>          <version>       <desc>
  yangrenke     2013/08/22      1.0             build this moudle  
**************************************************************/

#include <stdlib.h>
#include <signal.h>

#include <boost/thread.hpp>
#include <string.h>

#include "WorkTask.h"
#include "Logger.h"
#include "IniFile.h"


using namespace std;

int main( )
{

	//---- init ----------------- 
	IniFile ini;
	ini.LoadIniFile("../INI/WorkTask.ini");


	//--- hadoop's  and hive's  path -----
	string strHadoopPath = ini.GetString("TASK", "HADOOP_PATH", "/usr/local/hadoop/bin");
	string strHivePath = ini.GetString("TASK", "HIVE_PATH", "/usr/local/hadoop/bin");	
	ServerPath spNode;
	spNode.strHadoopPath = strHadoopPath;
	spNode.strHivePath = strHivePath;


	//-- init database------
	DBConfig dbC;
	dbC.strServer = ini.GetString("DATABASE", "SERVER", "localhost");
	dbC.strDB = ini.GetString("DATABASE", "DB", "");
	dbC.strUser = ini.GetString("DATABASE", "USER", "");
	dbC.strPassWord = ini.GetString("DATABASE", "PASSWORD", "");
	

	//--- init log ----
	string log_file = ini.GetString("MONTHLOG","LOG_FILE","../Log/Month");
	int log_level = ini.GetInteger("MONTHKLOG","LOG_LEVEL",9);
	int log_type = ini.GetInteger("MONTHLOG","LOG_TYPE",1);


	string strPath = log_file;
	if(strPath.length() && strPath.at(strPath.length()-1)!='/')
	{
		strPath.append("/");
	}	

	LogManager::CreateLongDirectory(strPath);
	LogManager::SetLogFilePath(log_file.c_str());
	LogManager::Open("MonthWork", log_type);
	LogManager::SetLogLevel(log_level);

	Logger log;
	log.Info("service MonthWorkTask is running!");


	WorkTask hTask;
	
	string strType = "Month";
	int nResult = hTask.Init( strType, spNode, &dbC );
	if( 0 == nResult )
	{
		boost::thread heartbeatThread(boost::ref(hTask));
		heartbeatThread.join();
	}
	

	return 0;

}
