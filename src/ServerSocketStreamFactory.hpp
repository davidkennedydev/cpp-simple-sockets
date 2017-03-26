#pragma once

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iostream>
#include <list>
#include <thread>

#include "SocketBuffer.hpp"
#include "ServerSocketStream.hpp"

namespace simple {
	using boost::asio::ip::tcp;

	class ServerSocketStreamFactory {
	public:
		using Port = unsigned short;

		ServerSocketStreamFactory (const Port port);
		virtual ~ServerSocketStreamFactory () = default;

		ServerSocketStream & getSocket();

	private:
		Port port;
		std::list<ServerSocketStream> sockets;
	};

	ServerSocketStreamFactory::ServerSocketStreamFactory (const Port port) :
		port(port)
	{
	}

	ServerSocketStream & ServerSocketStreamFactory::getSocket() {
		sockets.emplace_back(port);
		return sockets.back();
	}

} /* simple */ 
