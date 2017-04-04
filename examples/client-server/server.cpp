#include "Socket.cpp" // Include simple sockets class.

#include <iostream>
#include <string>

using namespace simple; // Use the "simple" namespace
using namespace std;

int main(void) {

	Connection client(12345); // Waits for a client connections on 12345 and redirect they to one 10 ports between 20000 and 20009.

	// Everything bellow will be asynchronously executed to each client connected.
	string question;
	client >> question;

	std::cout << question << std::endl;

	client << "I am here!";

	// Send this message to all connected clients
	client.all << "We have a new client connected!";

	return 0;
}
