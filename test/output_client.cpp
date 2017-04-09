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
std::string expectedMessage = "I'm here!";
boost::system::error_code error;

/// Server side, boost pure implementation
/**
 * Open port listening for a connection,
 * when someone connects waits for a message.
 */
void server(void) {
	boost::asio::io_service io_service;

	const unsigned short port = 12345;
	tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), port));

	tcp::socket socket(io_service);
	acceptor.accept(socket);

	std::array<char, 100> buffer;

	bytesReaded = socket.read_some(
			boost::asio::buffer(buffer.data(), buffer.size()),
			error);
	message = std::string(buffer.begin(), buffer.begin() + bytesReaded);
}

#include "../src/ClientSocketStream.hpp"
#include <ostream>

/// Client side using simple sockets
/**
 * Connect to server and send a message.
 */
void client(void) {
	simple::ClientSocketStream out("localhost", 12345);

	out << expectedMessage << std::endl;
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
	assert(bytesReaded == expectedMessage.size() + 1);
	assert(message == expectedMessage + "\n");

	return 0;
}
