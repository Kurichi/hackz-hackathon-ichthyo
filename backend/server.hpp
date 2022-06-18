#ifndef _SERVER_H_
#define _SERVER_H_

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <set>

// using namespace boost::asio::ip;

class Server {
 private:
  static constexpr int BUF_SIZE = 60000;
  static constexpr int PORT = 1234;

  boost::asio::io_service io_service;
  boost::asio::ip::udp::socket sock;
  std::set<boost::asio::ip::udp::endpoint> clientList;

 public:
  Server();

  void start();
  void receive();
  void broadcast(const boost::asio::ip::udp::endpoint &endpoint,
                 const std::string &str);
};

#endif  // _SERVER_H_
