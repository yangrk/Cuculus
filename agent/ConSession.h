#ifndef CON_SESSION
#define CON_SESSION


#include "CuculusInc.h"
#include "Logger.h"

using namespace plib;
using namespace std;
using namespace boost::asio::ip;

class ConSession:public boost::enable_shared_from_this<ConSession>
{

public:
	ConSession( boost::asio::io_service& ioservice );
	~ConSession(){;}

	void Start();
	tcp::socket& GetSocket();


private:
	void HandleReadHead( const boost::system::error_code& error );
	void HandleReadBody( const boost::system::error_code& error );


private:

	tcp::socket m_socket;
 	char m_Data[1000];

	Logger Log;



};

#endif
