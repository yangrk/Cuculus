/*************************************************************
  Copyright (C), 2014
  File name: ConServer.cpp
  Author:yangrenke     Version : 1.0       Date:2014/12/3 
  Description:
  Others:       
  Function List:
  History:
    <author>    <time>    <version >    <desc>
   yangrenke    2014/12/25     1.0     build this moudle  

*************************************************************/


#include "ConServer.h"


ConServer::ConServer(boost::asio::io_service& io, const tcp::endpoint& endpoint)
		:m_ioService(io),m_acceptor(io, endpoint)
{

	shared_ptr<ConSession> pCSNode( new ConSession(m_ioService));
	m_acceptor.async_accept( pCSNode->GetSocket(), bind(&ConServer::HandleAccept, this, boost::asio::placeholders::error,pCSNode) );

}




void ConServer::HandleAccept( const system::error_code& ec, shared_ptr<ConSession> &pCSNode )
{
	
	if( ec )
	{
		//错误处理
		Log.Error("ConServer::HandleAccept(): accept client error!");
		return ;
	}

	// 处理操作
	// read config header
	pCSNode->Start();

	shared_ptr<ConSession> pCSNewNode( new ConSession(m_ioService));
        m_acceptor.async_accept( pCSNewNode->GetSocket(), bind(&ConServer::HandleAccept,this,boost::asio::placeholders::error,pCSNewNode) );
	
}


/*
void ConServer::HandleRead( const boost::system::error_code& ec )
{

	if( ec )
	{
		return;
	}

	

	string *pStrData = null;
	pStrData = new string();
	if( null != pStrData )
	{
		*pStrData = m_Data;
		recieveData.producer( pStrData );	

	}
		

	m_sock.close();
	m_sock.	


	
	TaskInfo tiNode;
	if( !tiNode.ParseFromIstream(&strData) )
	{
		//出错

		return;
	}
	
	

}
*/

