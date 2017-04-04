#include <thread>
#include <sys/types.h>
#include <signal.h>

#include "../../src/Connection.hpp"

using namespace simple;

const unsigned short PORT = 12346;
const std::string clientExpectedMessage = "messageToClient",
      serverExpectedMessage = "messageToServer";

std::string clientReceivedMessage, serverReceivedMessage;

void server() {
	std::thread thread([] () {
		Connection client(PORT);

		client << clientExpectedMessage << std::endl;
		client >> serverReceivedMessage;
	});
	std::this_thread::sleep_for(std::chrono::milliseconds(300));
	thread.detach();
	thread.~thread();
}

void client() {
	Connection server("localhost", PORT);

	server >> clientReceivedMessage;
	server << serverExpectedMessage << std::endl;
}

int main(void) {
	std::thread serverThread(server);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	client();

	serverThread.join();
	return 0;
}
