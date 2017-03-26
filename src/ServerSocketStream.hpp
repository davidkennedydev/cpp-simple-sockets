#pragma once

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>

#include "SocketBuffer.hpp"

namespace simple {
	using boost::asio::ip::tcp;

	class ServerSocketStream : public std::iostream {
	public:
		using Port = unsigned short;

		ServerSocketStream (const Port port);
		virtual ~ServerSocketStream () = default;

	private:
		SocketBuffer buffer;
	};

	ServerSocketStream::ServerSocketStream (const Port port) :
		std::iostream(&buffer)
	{
		tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), port));
		acceptor.accept(buffer.socket);
		acceptor.close();
	}

} /* simple */ 
