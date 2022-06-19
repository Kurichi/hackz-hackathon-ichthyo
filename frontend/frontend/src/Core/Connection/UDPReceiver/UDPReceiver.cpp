#include "stdafx.h"
#include "Core/Connection/UDPReceiver.h"
#include <thread>
#include "Core/Connection/SingletonSocket.h"

UDPReceiver::UDPReceiver() :
	socket(SingletonSocket::Get())
{}

std::string UDPReceiver::Receive(int receiveBufferSize) {
	//std::vector<char> recvBuf(receiveBufferSize);
	std::array<char, 60000> recvBuf;
	boost::asio::ip::udp::endpoint en;
	std::size_t len;
	std::stringstream ss;

	len = this->socket->receive_from(boost::asio::buffer(recvBuf), en);
	ss.write(recvBuf.data(), len);
	return ss.str();
}


