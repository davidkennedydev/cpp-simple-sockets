#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <unistd.h>

#include "ServerSocketStreamFactory.hpp"
#include "ClientSocketStream.hpp"

namespace simple {

  enum ServerConnectionType { SINGLE, MULTI };

  class Connection : public std::iostream {
   public:
    using Port = unsigned short;

    explicit Connection (const Port, 
        const ServerConnectionType = MULTI);

    Connection (const std::string ip, const Port);
    virtual ~Connection() {}

   private:
    union {
      ClientSocketStream stream;
      ServerSocketStreamFactory factory;
    };
  };

  Connection::Connection (const Port port, 
      const ServerConnectionType serverType) 
      : factory (port) {
    do {
      this->rdbuf(factory.getSocket().rdbuf());
      if (serverType == SINGLE) break;
    } while ( fork() ); // on father process repeat, child comes out
    // terminate construction of client connection
  }

  Connection::Connection (const std::string ip, const Port port) 
      : stream (ip, port) {
    this->rdbuf(stream.rdbuf());
  }
  
} /* simple */ 
