#include <streambuf>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>

namespace simple {
	using std::string;

	class SocketBuffer : std::streambuf {
		static constexpr unsigned int BUFFER_SIZE = 255;
	public:
		SocketBuffer (string address, unsigned short port);
		virtual ~SocketBuffer ();

		int_type overflow(int_type character) override;
		int sync() override;

	private:
		boost::asio::io_service io_service;
		boost::asio::ip::tcp::socket socket;
		boost::asio::ip::tcp::resolver resolver;
		boost::array<char, BUFFER_SIZE> outputBuffer;
	};

	SocketBuffer::SocketBuffer(string address, unsigned short port) :
		socket(io_service), resolver(io_service) {
		setp(outputBuffer.begin(), outputBuffer.end());

		using boost::asio::ip::tcp;
		
		tcp::resolver::query query(address, std::to_string(port));
		tcp::resolver::iterator endpoint = this->resolver.resolve(query);
		boost::asio::connect(this->socket, endpoint);
	}

	SocketBuffer::int_type SocketBuffer::overflow(SocketBuffer::int_type character) {
		if (character == EOF) return EOF;
		*pptr() = character;
		return 0;
	}

	int SocketBuffer::sync() {
		boost::system::error_code error_code;
		boost::asio::write(this->socket, boost::asio::buffer(this->outputBuffer), error_code);
		if (error_code == boost::asio::error::broken_pipe)
			return -1;	
		return 0;
	}
} /* simple */ 

