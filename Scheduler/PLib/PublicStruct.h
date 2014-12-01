

#ifndef PUBLIC_LIB_H
#define PUBLIC_LIB_H


#include <string.h>
using namespace std;



namespace plib
{
	typedef struct work_task_config
	{	
		string strCommandName;
		string strLocation;
		string strParameter;
		string strState;
		int nTaskType;
		int nLevelType; 
	} WorkTaskConfig;


	typedef struct db_config
	{
		string strServer;
		string strDB;
		string strUser;
		string strPassWord;
	} DBConfig;


	typedef struct server_path
	{
		string strHadoopPath;
		string strHivePath;
	} ServerPath;

}


#endif
