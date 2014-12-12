/*************************************************************
  Copyright (C), 2014
  File name: ConfSock.cpp
  Author:yangrenke     Version : 1.0       Date:2014/12/2 
  Description: 网络信息收发sock类实现
  Others:       
  Function List:
    1.ConfSock::ConfSock 构造函数，发起连接
    2.ConfSock::handle_connect 连接处理函数
    3.ConfSock::handle_read_header 消息头部处理
    4.ConfSock::handle_read_body 消息体处理
  History:
    <author>    <time>    <version >    <desc>
   yangrenke    2014/12/02     1.0     build this moudle  
*************************************************************/



#include <stdlib.h>
#include "ConfSock.h"



/************************************************************
 
  Function:  ConfSock::ConfSock() 
  Description:    
  Calls:         
  Called By:     
  Table Accessed: 
  Table Updated: 
  Input:  
        string  strComand:  the string of command
  Output:         
  Return:       
  Others:        

**************************************************************/
ConfSock::ConfSock(boost::asio::io_service& io_service, tcp::endpoint endpoint,tcp::endpoint local)
		: m_ioService(io_service), m_receiveSocket(io_service), 
              	m_acceptor(io_service, tcp::endpoint(boost::asio::ip::tcp::v4(), 9101))
{
/*
      m_socket.open(boost::asio::ip::tcp::v4());
      m_socket.bind(local);
      m_socket.async_connect(endpoint, boost::bind(&ConfSock::HandleConnect, this, boost::asio::placeholders::error));
*/
}










