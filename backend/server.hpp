#ifndef _SERVER_H_
#define _SERVER_H_

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <set>

// using namespace boost::asio::ip;
constexpr int MAX_BUF_SIZE = 1024;
constexpr int PORT = 1234;

class Server
{
private:
  boost::asio::io_service io_service;
  boost::asio::ip::udp::socket sock;
  std::set<boost::asio::ip::udp::endpoint> clientList;

public:
  Server();

  void start();
  void receive();
  void broadcast(boost::asio::ip::udp::endpoint endpoint, boost::array<char, MAX_BUF_SIZE> recv_buf);
};

#endif // _SERVER_H_
