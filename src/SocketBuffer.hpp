#include <streambuf>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/array.hpp>

namespace simple {
	using std::string;

	class SocketBuffer : public std::streambuf {
		static constexpr unsigned int BUFFER_SIZE = 255;
	public:
		SocketBuffer (string address, unsigned short port);
		virtual ~SocketBuffer ();

		int sync() override;

	protected:
		int underflow() override;

	private:
		boost::asio::io_service io_service;
		boost::asio::ip::tcp::socket socket;
		boost::asio::ip::tcp::resolver resolver;
		boost::array<char, BUFFER_SIZE> outputBuffer, inputBuffer;
	};

	SocketBuffer::SocketBuffer(string address, unsigned short port) :
		socket(io_service), resolver(io_service) {

		setp(outputBuffer.begin(), outputBuffer.end());
		setg(inputBuffer.end(), inputBuffer.end(), inputBuffer.end());

		using boost::asio::ip::tcp;
		
		tcp::resolver::query query(address, std::to_string(port));
		tcp::resolver::iterator endpoint = this->resolver.resolve(query);
		boost::asio::connect(this->socket, endpoint);
	}

	SocketBuffer::~SocketBuffer() {
		sync();
	}

	int SocketBuffer::sync() {
		boost::system::error_code error_code;
		boost::asio::write(this->socket, boost::asio::buffer(this->outputBuffer.data(), pptr() - pbase()), error_code);
		setp(outputBuffer.begin(), outputBuffer.end());
		
		return (error_code == boost::asio::error::broken_pipe)? -1 : 0;
	}

	int SocketBuffer::underflow() {
		boost::system::error_code error;

		std::size_t bytesReaded = socket.read_some(
				boost::asio::buffer(inputBuffer.data(),
					inputBuffer.size()),
				error);
		setg(inputBuffer.begin(), inputBuffer.begin(),
				inputBuffer.begin() + bytesReaded);

		return (int) bytesReaded? *gptr() : EOF;
	}
} /* simple */ 

