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
  // command line argument
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
    boost::array<char, BUF_SIZE> recv_buf;
    boost::asio::ip::udp::endpoint endpoint;

    size_t len = sock.receive_from(boost::asio::buffer(recv_buf), endpoint);
    clientList.insert(endpoint);

    // [receive] IP : port Size: recv_size
    debug((boost::format("[receive] %1% : %2% Size: %3%") % endpoint.address() %
           endpoint.port() % len)
              .str());

    // recv_buf to string
    std::stringstream ss;
    ss.write(recv_buf.data(), len);

    broadcast(endpoint, ss.str());
  }
  sock.close();
}

void Server::broadcast(const boost::asio::ip::udp::endpoint &endpoint,
                       const std::string &str) {
  for (const auto &client : clientList) {
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
      std::cout << "[command] Server shutdown..." << std::endl;
    } else if (str == "/log" || str == "/debug") {
      isDebug = !isDebug;
      std::cout << "[command] Debug mode switched" << std::endl;
    } else if (str == "/return") {
      isReturn = !isReturn;
      std::cout << "[command] Return mode switched" << std::endl;
    } else if (str == "/reset") {
      clientList.clear();
      std::cout << "[command] Reset client list" << std::endl;
    } else if (str == "/help") {
      std::cout << "===== COMMAND LIST =====\n";
      std::cout << "/close or /quit\n";
      std::cout << "shutdown server\n\n";
      std::cout << "/log or /debug\n";
      std::cout << "switch debug mode\n\n";
      std::cout << "/return\n";
      std::cout << "switch return mode\n\n";
      std::cout << "/reset\n";
      std::cout << "reset client list\n\n";

      std::cout << std::flush;
    } else {
      std::cout << "[warning] This command is not found" << std::endl;
    }
  }
}

void Server::debug(const std::string message) {
  if (!isDebug) return;

  std::cout << message << std::endl;
}
