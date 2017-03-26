#pragma once

#include <streambuf>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/array.hpp>
#include <boost/icl/interval_set.hpp>

namespace simple {
	boost::asio::io_service io_service;

	using std::string;
	using boost::asio::ip::tcp;

	class SocketBuffer : public std::streambuf {
		friend class ClientSocketStream;
		friend class ServerSocketStream;

		static constexpr unsigned int BUFFER_SIZE = 255;
	public:
		SocketBuffer();
		virtual ~SocketBuffer();

		int sync() override;

	protected:
		int underflow() override;

		boost::array<char, BUFFER_SIZE> outputBuffer, inputBuffer;

	private:
		tcp::socket socket;
	};

	SocketBuffer::SocketBuffer() : socket(io_service) {
		setp(outputBuffer.begin(), outputBuffer.end());
		setg(inputBuffer.end(), inputBuffer.end(), inputBuffer.end());
	}

	SocketBuffer::~SocketBuffer() {
		sync();
	}

	int SocketBuffer::sync() {
		using namespace boost;
		using namespace boost::asio;

		system::error_code error_code;
		const size_t filledLength = pptr() - pbase();
		mutable_buffers_1 buffer = asio::buffer(
				this->outputBuffer.data(),
				filledLength);

		write(this->socket, buffer, error_code);
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

