#include "server.hpp"

#include <boost/format.hpp>
#include <sstream>

Server::Server()
    : sock(io_service,
           boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), PORT)) {}

void Server::start() { receive(); }

void Server::receive() {
  while (true) {
    // 送られてきた音声情報が入る
    boost::array<char, BUF_SIZE> recv_buf;
    // しゃべった人情報
    boost::asio::ip::udp::endpoint endpoint;
    size_t len = sock.receive_from(boost::asio::buffer(recv_buf), endpoint);

    std::stringstream ss;
    ss.write(recv_buf.data(), len);

    clientList.insert(endpoint);

    broadcast(endpoint, ss.str());
  }
}

// endpoint を除く client 全員に送信
void Server::broadcast(const boost::asio::ip::udp::endpoint &endpoint,
                       const std::string &str) {
  auto buf = boost::asio::buffer(str);
  for (const auto &client : clientList) {
    // 送ってきた人とclientが同一なら読み飛ばす
    if (endpoint == client) continue;

    sock.send_to(
        buf, boost::asio::ip::udp::endpoint(client.address(), client.port()));
  }
}
