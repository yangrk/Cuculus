#include "ConSession.h"
//#include "ProtoMsg.pb.h"
#include "CuculusInc.h"
#include "ShareCycqueue.h"

extern ShareBuffer<string *> recieveData;


ConSession::ConSession( boost::asio::io_service& ioservice ):m_socket(ioservice)
{
        memset(m_Data,0,sizeof(m_Data));
}


tcp::socket& ConSession::GetSocket()
{

	return m_socket;

}


void ConSession::Start()
{
	//m_socket.async_read_some( boost::asio::buffer(m_Data, sizeof(m_Data)),boost::bind(&ConSession::HandleRead,this,boost::asio::placeholders::error));
	boost::asio::async_read(m_socket, boost::asio::buffer(m_Data, 8), 
		boost::bind(&ConSession::HandleReadHead,shared_from_this(),boost::asio::placeholders::error));

}



void ConSession::HandleReadHead( const boost::system::error_code& ec )
{

	if( !ec )
        {
		// decode head
		char header[9] = "";
		strncat(header, m_Data, 8);
		int nLen = atoi(header);
		
		cout<<"head is : "<<nLen<<endl;

		memset(m_Data,0,sizeof(m_Data));

		boost::asio::async_read(m_socket, boost::asio::buffer(m_Data, nLen), 
                	boost::bind(&ConSession::HandleReadBody,shared_from_this(), boost::asio::placeholders::error));
		
        }
	else
	{
		Log.Error("ConSession::HandleReadHead(): some errors in data! error is (%s)", ec.message().c_str());
                return;
		
	}

}


void ConSession::HandleReadBody( const boost::system::error_code& ec )
{
	cout<<"body is : "<<m_Data<<endl;

	if( !ec )
	{
		
                string *pStrData = NULL;
                pStrData = new string();
                if( NULL != pStrData )
                {
                        pStrData->assign(m_Data, strlen(m_Data));
                        recieveData.producer( pStrData );
                }

		
		memset(m_Data,0,sizeof(m_Data));	
		boost::asio::async_read(m_socket, boost::asio::buffer(m_Data, 8),
                	boost::bind(&ConSession::HandleReadHead, shared_from_this(), boost::asio::placeholders::error));

	}
	else
	{

		Log.Error("ConSession::HandleReadBody(): some errors in data! error is (%s)", ec.message().c_str());
                return;
	}
	
}


