#include "server.hpp"

#include <boost/format.hpp>
#include <sstream>
#include <thread>

Server::Server()
    : sock(io_service,
           boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), PORT)) {}

void Server::start() {
	receive();
//  std::thread thd_receive(&Server::receive, this);
 // std::thread thd_command(&Server::command, this);
 // thd_receive.join();
 // thd_command.join();
}

void Server::receive() {
  while (isLoop) {
    // 送られてきた音声情報が入る
    boost::array<char, BUF_SIZE> recv_buf;
    // しゃべった人情報
    boost::asio::ip::udp::endpoint endpoint;
    size_t len = sock.receive_from(boost::asio::buffer(recv_buf), endpoint);

    std::cout << "receive" << std::endl;

    std::stringstream ss;
    ss.write(recv_buf.data(), len);

    clientList.insert(endpoint);

    broadcast(endpoint, ss.str());
  }
  sock.close();
}

// endpoint を除く client 全員に送信
void Server::broadcast(const boost::asio::ip::udp::endpoint &endpoint,
                       const std::string &str) {
  for (const auto &client : clientList) {
    // 送ってきた人とclientが同一なら読み飛ばす
    //if (endpoint == client) continue;

    sock.send_to(
	boost::asio::buffer(str),
        boost::asio::ip::udp::endpoint(client.address(), client.port()));
  }
}

void Server::command() {
  while (isLoop) {
    std::string str;
    std::cin >> str;

    if (str == "/close" || str == "/quit") {
      isLoop = false;
    }
  }
}
