#ifndef _SERVER_H_
#define _SERVER_H_

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <string>

class Server {
 private:
  std::vector<boost::asio::ip::udp::endpoint> endpointList;

 public:
  Server();

  void start();

  void receive();

  void broadcast();
};

#endif  // _SERVER_H_
