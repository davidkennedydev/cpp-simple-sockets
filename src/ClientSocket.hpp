#include <string>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>

#include "SocketBuffer.hpp"

namespace simple {
	using std::string;
	using boost::asio::ip::tcp;

	class ClientSocket : public std::istream, public std::ostream {
	public:
		using Port = unsigned short;

		ClientSocket (string address, Port port);
		virtual ~ClientSocket() = default;

	private:
		tcp::resolver resolver;
		SocketBuffer buffer;
	};

	ClientSocket::ClientSocket(string address, Port port) :
		std::istream(&this->buffer), std::ostream(&this->buffer), 
		resolver(io_service) {
		
		tcp::resolver::query query(address, std::to_string(port));
		tcp::resolver::iterator endpoint = 
			this->resolver.resolve(query);
		boost::asio::connect(this->buffer.socket, endpoint);
	}

} /* simple */ 

