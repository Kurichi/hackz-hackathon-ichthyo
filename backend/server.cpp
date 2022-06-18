#include "server.hpp"
#include <boost/format.hpp>

Server::Server() : sock(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), PORT))
{
}

void Server::start()
{
    receive();
}

void Server::receive()
{
    while (true)
    {
        // 送られてきた音声情報が入る
        boost::array<char, MAX_BUF_SIZE> recv_buf;
        // しゃべった人情報
        boost::asio::ip::udp::endpoint endpoint;
        size_t len = sock.receive_from(boost::asio::buffer(recv_buf), endpoint);
	std::cout << "receive" << std::endl;

	std::stringstream ss;
	ss.write(recv_buf.data(), len);

        clientList.insert(endpoint);

 broadcast(endpoint, ss.str());
    }
}

// endpoint を除く client 全員に送信
void Server::broadcast(boost::asio::ip::udp::endpoint endpoint, const std::string &str)
{
	//std::string str(recv_buf.begin(), recv_buf.end());
//	std::string str = "Hello";
    for (const auto &client : clientList)
    {
        // 送ってきた人とclientが同一なら読み飛ばす
        //if (endpoint == client)
         //   continue;

        sock.send_to(
            boost::asio::buffer(str),
            boost::asio::ip::udp::endpoint(client.address(), client.port()));
    }
}
