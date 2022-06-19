#ifndef _SERVER_H_
#define _SERVER_H_

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <set>
#include <string>

class Server {
 private:
  static constexpr int BUF_SIZE = 60000;
  static constexpr int PORT = 1234;

  boost::asio::io_service io_service;
  boost::asio::ip::udp::socket sock;
  std::set<boost::asio::ip::udp::endpoint> clientList;

  bool isLoop = true;

  bool isDebug = false;
  bool isReturn = false;

 public:
  Server();
  Server(const std::vector<std::string>& args);

  void start();
  void receive();
  void broadcast(const boost::asio::ip::udp::endpoint& endpoint,
                 const std::string& str);
  void command();
  void debug(const std::string message);
};

#endif  // _SERVER_H_
