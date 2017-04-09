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
    virtual ~Connection() = default;

   private:

    union SocketStreamUnion {
      ClientSocketStream stream;
      ServerSocketStreamFactory factory;

      SocketStreamUnion(Port port) : factory(port) {}
      SocketStreamUnion(std::string ip, Port port) : stream(ip, port) {}
      ~SocketStreamUnion() {}
    } socketUnion;
  };

  Connection::Connection (const Port port, 
      const ServerConnectionType serverType) 
      : std::iostream(nullptr), socketUnion(port) {
    do {
      this->rdbuf(socketUnion.factory.getSocket().rdbuf());
      if (serverType == SINGLE) break;
    } while ( fork() ); // on father process repeat, child comes out
    // terminate construction of client connection
  }

  Connection::Connection (const std::string ip, const Port port) 
      : std::iostream(nullptr), socketUnion(ip, port) {
    this->rdbuf(socketUnion.stream.rdbuf());
  }
  
} /* simple */ 
