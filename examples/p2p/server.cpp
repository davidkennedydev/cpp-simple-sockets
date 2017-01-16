#include "Socket.cpp" // Include simple sockets class.

#include <iostream>
#include <string>

using namespace simple; // Use the "simple" namespace
using namespace std;

int main(void) {

	Socket socket(12345); // Waits for a client connection.

	string question;
	socket >> question;

	std::cout << question << std::endl;

	socket << "I am here!";

	return 0;
}
