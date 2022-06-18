#include "server.hpp"

#include <boost/format.hpp>
#include <future>
#include <sstream>
#include <thread>

Server::Server()
    : sock(io_service,
           boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), PORT)) {}

Server::Server(const std::vector<std::string> &args)
    : sock(io_service,
           boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), PORT)) {
  for (const auto &arg : args) {
    if (arg == "--debug") {
      std::cout << "[option] Debug mode" << std::endl;
      isDebug = true;
    } else if (arg == "--return") {
      std::cout << "[option] Return speaker" << std::endl;
      isReturn = true;
    }
  }
}

void Server::start() {
  std::cout << "Server listening..." << std::endl;

  std::thread thd_receive(&Server::receive, this);
  std::thread thd_command(&Server::command, this);
  thd_receive.join();
  thd_command.join();
}

void Server::receive() {
  while (isLoop) {
    // 送られてきた音声情報が入る
    boost::array<char, BUF_SIZE> recv_buf;
    // しゃべった人情報
    boost::asio::ip::udp::endpoint endpoint;

    size_t len = sock.receive_from(boost::asio::buffer(recv_buf), endpoint);
    clientList.insert(endpoint);

    debug((boost::format("[receive] %1% : %2%") % endpoint.address() %
           endpoint.port())
              .str());

    std::stringstream ss;
    ss.write(recv_buf.data(), len);
    /* std::thread thd(&Server::broadcast, this, endpoint, ss.str()); */
    broadcast(endpoint, ss.str());
  }
  sock.close();
}

// endpoint を除く client 全員に送信
void Server::broadcast(const boost::asio::ip::udp::endpoint endpoint,
                       const std::string str) {
  for (const auto &client : clientList) {
    // 送ってきた人とclientが同一なら読み飛ばす
    if (endpoint == client && !isReturn) continue;

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
    } else if (str == "/log" || str == "/debug") {
      isDebug = !isDebug;
    } else if (str == "/return") {
      isReturn = !isReturn;
    } else if (str == "/help") {
      std::cout << "===== COMMAND LIST =====\n";
      std::cout << "/close or /quit\n";
      std::cout << "shutdown server\n\n";
      std::cout << "/log or /debug\n";
      std::cout << "switch debug mode\n\n";
      std::cout << "/return\n";
      std::cout << "switch return mode\n\n";

      std::cout << std::flush;
    }
  }
}

void Server::debug(std::string message) {
  if (!isDebug) return;

  std::cout << message << std::endl;
}
