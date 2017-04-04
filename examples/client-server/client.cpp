#include "Socket.cpp" // Include simple sockets class.

#include <iostream>
#include <string>

using namespace simple; // Use the "simple" namespace
using namespace std; 

int main(void) {

	Connection server("localhost", "12345"); // Open a connection with the server.

	server << "Is someone there?"; 

	string response;
	server >> response;

	std::cout << response << std::endl;

	return 0;
}
