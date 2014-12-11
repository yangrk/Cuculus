/*************************************************************
  Copyright (C), 2014
  File name: ConfSock.H
  Author:yangrenke     Version : 1.0       Date:2014/12/2 
  Description: 网络信息收发sock类头文件
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

#ifndef CONF_SOCK_H
#define CONF_SOCK_H

#include "CuculusInc.h"
using boost::asio::ip::tcp;


class ConfSock
{
public:

  ConfSock(boost::asio::io_service&, tcp::endpoint, tcp::endpoint );

  void Close();
  void Run();


private:
  void HandleConnect( const boost::system::error_code& );
  void HandleRead( const boost::system::error_code& );
  void DoClose( tcp::socket* );

private:
  boost::asio::io_service& m_ioService;
  tcp::socket m_receiveSocket;
  boost::asio::ip::tcp::acceptor m_acceptor;


};






#endif

