/*************************************************************
 
  Copyright (C), 2014
  File name: ConServer.h
  Author:yangrenke     Version : 1.0       Date:2014/12/3 
  Description: 配置信息获取服务头文件
  Others:       
  Function List:
    1.CuculusTimer: 构造函数，初始化定时工作的时间以及间隔
    2.Run： 外部调用，启动定时器
    3.TimerFunc： 定时器的业务处理函数
  History:
    <author>    <time>    <version >    <desc>
   yangrenke    2014/12/24     1.0     build this moudle 

***************************************************************/

#ifndef CON_SERVER_H
#define CON_SERVER_H


#include "CuculusInc.h"
#include "Logger.h"
#include "ConSession.h"

using namespace plib;
using namespace std;
using namespace boost::asio::ip;

class ConServer
{

public:

	ConServer(boost::asio::io_service& io_service, const tcp::endpoint& endpoint);
	void HandleAccept(const boost::system::error_code& error, shared_ptr<ConSession> &pCSNode);


private:
	//int UpdateTaskIDList();//
	//int UpdateTaskShareQueue( );
	//int UpdateDB();	



private:

	boost::asio::io_service& m_ioService;
	tcp::acceptor m_acceptor;

	Logger Log;



};

#endif
