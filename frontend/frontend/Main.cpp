# include <Siv3D.hpp> // OpenSiv3D v0.6.4
#include "Core/Audio/UsersVoicePlayer.h"
#include "Core/Connection/SingletonSocket.h"
#include "Core/Audio/UserVoiceRecorder.h"

using namespace boost::asio::ip;
using namespace boost::asio;

void Main()
{
	UserVoiceRecorder recorder(udp::endpoint(ip::address::from_string("127.0.0.1"),23236));
	SingletonSocket::SetMyEndpoint(udp::endpoint(udp::v4(), 23233));
	//UsersVoicePlayer player(
	//	udp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 23234
	//	));
	//player.ReceiveAndPlayLoop();





	while (System::Update()){

		
	}
}

