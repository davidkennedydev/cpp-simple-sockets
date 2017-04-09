/// Simple sockets buffer output client test
/// This test cover if simple socket client can send message to a boost based
/// server application.

#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <memory>
#include <list>
#include <assert.h>
#include <sstream>

using boost::asio::ip::tcp;

size_t bytesReaded;
std::string message;
std::string expectedMessage = "I'm here!\n";
boost::system::error_code error;

const int PORT = 12346;

/// Server side, boost pure implementation
/**
 * Open port listening for a connection,
 * when someone connects send a message.
 */
void server(void) {
	boost::asio::io_service io_service;

	const unsigned short port = PORT;
	tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), port));

	tcp::socket socket(io_service);
	acceptor.accept(socket);

	boost::asio::write(socket, boost::asio::buffer(expectedMessage), error);
}

#include "../src/ClientSocketStream.hpp"
#include <istream>

/// Client side using simple sockets
/**
 * Connect to server and receive a message.
 */
void client(void) {
	using namespace simple;

	ClientSocketStream in("localhost", PORT);
	
	std::string word;

	in >> word;
	message += word;
	message += ' ';
	in >> word;
	message += word;
	message += '\n';

	bytesReaded = message.size();
}

#include <thread>

/// Main test
/**
 * Start server take a while and start client.
 * Then test if communication is ok.
 */
int main(void) {
	std::thread serverRun(server);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	client();
	serverRun.join();
	
	assert(error == 0);
	assert(bytesReaded == expectedMessage.size());
	assert(message == expectedMessage);

	return 0;
}
