#pragma once
#include <boost/asio.hpp>
#include <memory>

class SingletonSocket {
private:
	static boost::asio::io_service io_service;
	static std::shared_ptr<boost::asio::ip::udp::socket> socket;
	static boost::asio::ip::udp::endpoint endpoint;
	SingletonSocket() {}
public:
	static void SetMyEndpoint(const boost::asio::ip::udp::endpoint& ep) {
		SingletonSocket::endpoint = ep;
	}

	static std::shared_ptr<boost::asio::ip::udp::socket> Get() {
		if (socket == nullptr) {
			socket = std::make_shared<boost::asio::ip::udp::socket>(io_service, endpoint);
			return socket;
		}
		return socket;
	}
};

