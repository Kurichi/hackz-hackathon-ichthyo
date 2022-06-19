#include "Core/Connection/SingletonSocket.h"

boost::asio::io_service SingletonSocket::io_service;
std::shared_ptr<boost::asio::ip::udp::socket> SingletonSocket::socket;
boost::asio::ip::udp::endpoint SingletonSocket::endpoint;
