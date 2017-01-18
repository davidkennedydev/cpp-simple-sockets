#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <string>

namespace simple {
	class ClientSocket {
	public:
		ClientSocket (std::string address, int port);
		virtual ~ClientSocket ();

		ClientSocket operator <<(const std::string &message);
		ClientSocket operator >>(std::string &message);
	
	private:
		boost::asio::io_service io_service;
	};

	class ServerSocket {
	public:
		ServerSocket (int port);
		virtual ~ServerSocket ();
	
		ServerSocket operator <<(const std::string &message);
		ServerSocket operator >>(std::string &message);
	private:
		boost::asio::io_service io_service;
	};

} /* simple */ 
