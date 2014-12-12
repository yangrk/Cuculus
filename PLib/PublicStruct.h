

#ifndef PUBLIC_LIB_H
#define PUBLIC_LIB_H


#include <string.h>
#include <ext/hash_map>


using namespace std;
using namespace __gnu_cxx;



namespace plib
{
	typedef struct work_job_config
	{
		int   nId;
		string strCommandName;
		string strLocation;
		string strParameter;
		int nTaskType;
	} WorkJobConfig;




	typedef struct work_task_config
	{
		int nId;
		string strExecuteTime;
		string strTaskChain;
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

 	typedef	hash_map<int, WorkJobConfig> JobItemHash;
}


#endif