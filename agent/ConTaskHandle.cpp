
#include "ConTaskHandle.h"
#include "ShareCycqueue.h"

using namespace boost;
using namespace plib;


extern ShareBuffer<WorkTaskConfig *> yearJobBuf;
extern hash_set<int> HashSetYearTaskID;

extern ShareBuffer<string *> recieveData;


int ConTaskHandle::Init( string& strIniFilePath )
{

	 // init the ini file
	 InitIni( strIniFilePath );


	//init db
	int nResult = InitDBConnection();
	if( 0 != nResult )
	{
		Log.Error("ConTaskHandle::Init(): init failed!");
		return -1;		
	}

	Log.Info("ConTaskHandle::Init(): init success!");
	return 0;

}


void ConTaskHandle::InitIni( string & strPath )
{
	m_ini.LoadIniFile( strPath.c_str() );
}


int ConTaskHandle::InitDBConnection()
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
                bool bR = m_pDB->connect( (m_dbC.strDB).c_str(), (m_dbC.strServer).c_str(), (m_dbC.strUser).c_str(), (m_dbC.strPassWord).c_str());
		if( !bR )	
		{
			 // fail to connect db
                        Log.Error("ConTaskHandle::InitDBConnection(): connect to db failed!");
                        return -1;		
		}

	}
	catch(const mysqlpp::Exception& er)
	{
		Log.Error("ConTaskHandle::InitDBConnection(): Error:%s[%d:%d]\n",(er.what()),__FILE__,__LINE__);
                return -1;

	}
	

	Log.Info("ConTaskHandle::InitDBConnection(): init success!");
        
	return 0;

}





int ConTaskHandle::operator()( )
{

	while( true )
	{
		string *pValue = recieveData.consumer();

		cout<<"ConTaskHandle recive size is :"<<pValue->size()<<endl;

		TaskInfo tiNode;
        	if( !tiNode.ParseFromString(*pValue) )
		{
			cout<<" o type is "<<tiNode.noperatetype()<<endl;

			//出错
			Log.Error("ConTaskHandle::operator(): parse data error!");
			delete pValue;
                	pValue = NULL;
			continue;
		}


		DispatchData( tiNode );

		delete pValue;
		pValue = NULL;

	}
}




void ConTaskHandle::DispatchData( TaskInfo& tiNode )
{

	if( 1 == tiNode.noperatetype() )
	{	
		//add task
		AddTask( tiNode );
	}
	else if( 2 == tiNode.noperatetype() )
	{
		//delete task
		DeleteTask( tiNode );
	}
	else if( 3 == tiNode.noperatetype() )
	{
		//update task
		//UpdateTask( tiNode );
	}

	return ;
}


int ConTaskHandle::AddTask( TaskInfo& tiNode )
{
	
	int nResult = 0;
	int nIndex = 0;
	string strTable;

	int nTaskType = tiNode.ntasktype();
	switch( nTaskType )
	{
	case 1:
	//年
	//1.add to db
	 Log.Debug("ConTaskHandle::AddTask(): task type is year!");	

	strTable = "tb_con_task_year";
	nResult = InsertToDB( tiNode, strTable );	
	if( 0 == nResult )
	{
		nIndex = GetCurrentDBIndex();
		if( 0 != nIndex )
		{
			//2. add to hash set
			hash_set<int>::iterator it = HashSetYearTaskID.find( nIndex );
			if( it == HashSetYearTaskID.end() )
			{
				HashSetYearTaskID.insert( nIndex );

				//3. add to yeartask list buf
				WorkTaskConfig *pConfigSet = new WorkTaskConfig();
				pConfigSet->nId = nIndex;
				(pConfigSet->strExecuteTime).assign(tiNode.strexetime());
                     		(pConfigSet->strTaskChain).assign(tiNode.strtaskchain());
                      
                    		yearJobBuf.producer( pConfigSet );

				Log.Info("ConTaskHandle::AddTask(): add task %d to hash_set succes!",pConfigSet->nId);

			}
		}
	}
	break;

	case 2:
	//季度

	break;

	case 3:
	//月
	
	break;

	case 4:
	//周
	
	break;

	case 5:
	//日
	
	break;


	case 6:
	//小时

	break;

	case 7:
	//指定时刻

	break;

	case 8:
	//立即执行

	break;
	default:

	break;

	}

}



int ConTaskHandle::DeleteTask( TaskInfo& tiNode )
{

	//int nIndex = 0;
	int nResult = 0;
	string strTable;

	int nId = tiNode.ntaskid();
	int nTaskType = tiNode.ntasktype();
	switch( nTaskType )
	{
	case 1:
		//年
		//1. delete from db

		Log.Debug("ConTaskHandle::DeleteTask(): task type is year!");

		strTable = "tb_con_task_year";
		nResult = DeleteFromDB( nId, strTable );
		if( 0 == nResult )
		{
			// delete from hash set
			hash_set<int>::iterator it = HashSetYearTaskID.find( nId );
			if( it != HashSetYearTaskID.end() )
                	{
				HashSetYearTaskID.erase(it);
				Log.Info("ConTaskHandle::DeleteTask(): delete %d from hash_set success!", nId);
			}
		}

	break;

	case 2:
	//季度	


	break;

	case 3:
	//月


	break;

	case 4:
	//周

	break;

	case 5:
	//日

	break;

	case 6:
	//小时
	break;
	
	case 7:
	//指定时刻

	break;

	case 8:
	//立即执行
	

	break;

	default:

	break;


	}


	return 0;	

}






int ConTaskHandle::InsertToDB( TaskInfo& tiNode, string strTable )
{

	
	try{
		mysqlpp::Query query = m_pDB->query();
		query<<" insert into "<<strTable<<" values"<<"("<<0<<","<<"'"<<tiNode.strexetime()<<"'"<<","
			<<"'"<<tiNode.strtaskchain()<<"'"<<","<<"'"<<tiNode.strcomment()<<"'"
			<<","<<"'"<<tiNode.strcreatetime()<<"'"<<")";
		
		mysqlpp::SimpleResult sim_res = query.execute();
		query.reset();

		Log.Info("ConTaskHandle::InsertToDB(): insert to table  %s success!( %s, %s, %s ) ", 
		strTable.c_str(), tiNode.strexetime().c_str(), tiNode.strtaskchain().c_str(), tiNode.strcomment().c_str() );
	
	
 	}catch( const mysqlpp::ConnectionFailed& ce )
	{
		//Something went wrong with the connect
		Log.Error("ConTaskHandle::InsertToDB():Connection failed:%s[%d:%d]",(ce.what()),__FILE__,__LINE__);
		return -1;
	}	
	catch (const mysqlpp::BadQuery& ce) 
	{
		// Something went wrong with the SQL query.
		Log.Error("ConTaskHandle::InsertToDB():Query failed:%s[%d:%d]",(ce.what()),__FILE__,__LINE__);
		return -1;
	}
	catch (const mysqlpp::Exception& ce)
	{
		// Catch-all for any other MySQL++ exceptions
		Log.Error("ConTaskHandle::InsertToDB():Error:%s[%d:%d]",(ce.what()),__FILE__,__LINE__);
		return -1;
	}

	return 0;
}



int ConTaskHandle::DeleteFromDB( int nId, string strTable )
{

	try{
		mysqlpp::Query query = m_pDB->query();
		query<<" delete from "<<strTable<<" where id="<<nId;
		
		mysqlpp::SimpleResult sim_res = query.execute();
                query.reset();

		Log.Info("ConDTaskHandle::DeletefromDB(): delete id(%d) from %s success!", nId,strTable.c_str());


	}catch( const mysqlpp::ConnectionFailed& ce )
	{
		//Something went wrong with the connect
		Log.Error("ConDTaskHandle::DeletefromDB():Connection failed:%s[%d:%d]",(ce.what()),__FILE__,__LINE__);
                return -1;

	}
	catch (const mysqlpp::BadQuery& ce)
	{
		// Something went wrong with the SQL query.
		Log.Error("ConDTaskHandle::InsertToDB():Query failed:%s[%d:%d]",(ce.what()),__FILE__,__LINE__);
		return -1;
	}
	catch (const mysqlpp::Exception& ce)
	{
		// Catch-all for any other MySQL++ exceptions
		Log.Error("ConDTaskHandle::DeletefromDB():Error:%s[%d:%d]",(ce.what()),__FILE__,__LINE__);
		return -1;
	}

	return 0;

}





int ConTaskHandle::GetCurrentDBIndex( )
{
	int nIndex = 0;
	try
	{
		mysqlpp::Query query = m_pDB->query();
                string sql = std::string("select LAST_INSERT_ID()");

                query<<sql;
                mysqlpp::StoreQueryResult res = query.store();
		if(  res.num_rows() > 0 )
		{
			nIndex = res[0][0];
		}
	
		Log.Debug("ConDTaskHandle::GetCurrentDBIndex: get index from db, index is :%d", nIndex);

	}
	catch (const mysqlpp::ConnectionFailed& ce)
	{
		Log.Error("ConDTaskHandle::GetCurrentDBIndex:Connection failed:%s[%d:%d]",(ce.what()),__FILE__,__LINE__);
	}
	catch (const mysqlpp::BadQuery& e)
        {		
		// Something went wrong with the SQL query
		Log.Error("ConDTaskHandle::GetCurrentDBIndex:Query failed:%s[%d:%d]",(e.what()),__FILE__,__LINE__);
	}
	catch (const mysqlpp::Exception& er)
        {
		// Catch-all for any other MySQL++ exceptions
		Log.Error("ConDTaskHandle::GetCurrentDBIndex:Error:%s[%d:%d]",(er.what()),__FILE__,__LINE__);
	}

	return nIndex;

}





















