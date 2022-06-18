# include <Siv3D.hpp> // OpenSiv3D v0.6.4
#include "Core/Audio/UsersVoicePlayer.h"
#include "Core/Connection/SingletonSocket.h"
#include "Core/Audio/UserVoiceRecorder.h"
#include "Core/User.h"

using namespace boost::asio::ip;
using namespace boost::asio;

void Main()
{
	system("explorer .");
	SingletonSocket::SetMyEndpoint(udp::endpoint(udp::v4(), 32153));
	UserVoiceRecorder recorder(udp::endpoint(address::from_string("219.94.241.220"), 1234));

	//UserVoiceRecorder recorder(udp::endpoint(ip::address::from_string("127.0.0.1"), 23236));
	//SingletonSocket::SetMyEndpoint(udp::endpoint(udp::v4(), 32153));
	//SingletonSocket::Get()->connect(udp::endpoint(ip::address::from_string("127.0.0.1"), 23236));
	UsersVoicePlayer player(
		udp::endpoint(boost::asio::ip::address::from_string("219.94.241.220"), 1234
	));

	std::thread playThread([&] {
		player.ReceiveAndPlayLoop();
		});
		

	
	while (System::Update()){
		recorder.SendAudioData({ "name", "1edfa37547" });
		//recorder.SendAudioData({"name", "id"});
		if (KeyLeft.pressed()) {
			SingletonSocket::Get()->close();
			std::this_thread::sleep_for(std::chrono::seconds(1));
			return;
		}


		
	}
}

