#pragma once
#include <boost/asio.hpp>

class UDPReceiver {
private:
	boost::asio::io_service io_service;
	std::shared_ptr<boost::asio::ip::udp::socket> socket;
public:
	UDPReceiver();
	std::string Receive(int receiveBufferSize = 1000);
};

