#include <string>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>

#include "SocketBuffer.hpp"

namespace simple {
	using std::string;
	using boost::asio::ip::tcp;

	class ClientSocketStream : public std::iostream {
	public:
		using Port = unsigned short;

		ClientSocketStream (string address, Port port);
		virtual ~ClientSocketStream() = default;

	private:
		tcp::resolver resolver;
		SocketBuffer buffer;
	};

	ClientSocketStream::ClientSocketStream(string address, Port port) :
		std::iostream(&this->buffer), 
		resolver(io_service) {
		
		tcp::resolver::query query(address, std::to_string(port));
		tcp::resolver::iterator endpoint = 
			this->resolver.resolve(query);
		boost::asio::connect(this->buffer.socket, endpoint);
	}

} /* simple */ 

