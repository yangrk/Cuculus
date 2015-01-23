#ifndef CON_TASK_HANDLE
#define CON_TASK_HANDLE

#include <mysql++.h>
#include <string.h>

#include "CuculusInc.h"
#include "Logger.h"
#include "IniFile.h"
#include "ProtoMsg.pb.h"
#include "PublicStruct.h"

using namespace plib;
using namespace std;
using namespace protomsg;

class ConTaskHandle
{

public:
	ConTaskHandle(){;}
	~ConTaskHandle(){;}
	
	int Init( string & );
	int operator()();


private:
	void InitIni( string & );
	int InitDBConnection();
	void DispatchData( TaskInfo& );
	
	int AddTask( TaskInfo& );
	int DeleteTask( TaskInfo& );
	int UpdateTask( TaskInfo& );

	int InsertToDB( TaskInfo&, string );
	int DeleteFromDB( int, string );
	int GetCurrentDBIndex();

private:
	IniFile m_ini;
        DBConfig m_dbC;
	mysqlpp::Connection *m_pDB;
	Logger Log;


};
#endif


