#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <thread>

int main() {
  using namespace boost::asio::ip;

  int port;
  std::cin >> port;

  boost::asio::io_service io_service;
  udp::socket sock(io_service, udp::endpoint(udp::v4(), port));

  while (true) {
    std::string str;
    std::cin >> str;

    sock.send_to(boost::asio::buffer(str),
                 udp::endpoint(address::from_string("127.0.0.1"), 1234));

    //受信（受信できるまで待機される）
    boost::array<char, 128> recv_buf;
    udp::endpoint endpoint;
    size_t len = sock.receive_from(boost::asio::buffer(recv_buf), endpoint);

    //受信内容を表示
    std::cout.write(recv_buf.data(), len);
  }
}
