#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <unistd.h>

#include "ServerSocketStreamFactory.hpp"
#include "ClientSocketStream.hpp"

namespace simple {

	class Connection : public std::iostream {
	public:
		using Port = unsigned short;

		Connection (Port);
		Connection (std::string ip, Port);
		virtual ~Connection() {}

	private:
		union {
			ClientSocketStream stream;
			ServerSocketStreamFactory factory;
		};
	};

	Connection::Connection (Port port) :
		factory (port)
       	{
		pid_t pid;
		do {
			this->rdbuf(factory.getSocket().rdbuf());
			pid = fork();
		} while (pid != 0);
	}

	Connection::Connection (std::string ip, Port port) :
		stream (ip, port)
	{
		this->rdbuf(stream.rdbuf());
	}
	
} /* simple */ 
