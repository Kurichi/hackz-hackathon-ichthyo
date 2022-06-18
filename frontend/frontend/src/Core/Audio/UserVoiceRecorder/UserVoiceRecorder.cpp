#include "stdafx.h"
#include "Core/Audio/UserVoiceRecorder.h"
#include "Core/User.h"
#include <format>
#include "Core/Util.h"

using namespace boost::asio::ip;

UserVoiceRecorder::UserVoiceRecorder(const udp::endpoint& serverEndpoint) :
	tmpAudioFileDirectory("tmpAudio"),
	previousSendedTime(0),
	recorder(),
	serverEndpoint(serverEndpoint),
	socket(SingletonSocket::Get()),
	sock(ios, udp::endpoint(address::from_string("127.0.0.1"), 32153))
{
	this->recorder.SetMicrophoneRecordDuration(1s);
}

void UserVoiceRecorder::SendAudioData(const User& myUser ) {

	static std::unique_ptr<std::thread> sendAudioThreadPtr = nullptr;
	if (this->previousSendedTime + 1 > Scene::Time()) {
		return;
	}
	boost::asio::io_service io_service;
	previousSendedTime = Scene::Time();
	Wave wave = recorder.GetRecentWave();
	if (sendAudioThreadPtr != nullptr)
	{
		sendAudioThreadPtr->join();
	}

	sendAudioThreadPtr.reset(new std::thread([wave, &myUser, this]{
		const std::string audioPath = (this->tmpAudioFileDirectory / "hoge.ogg").string();
		if (!wave.save(Unicode::Widen(audioPath))) {
			return;
		}

		std::string data = std::format("{}\n{}\n{}\n{}\n", myUser.name, "uuid", 0, 1);
		std::string tmp;

		Util::ReadBinary(tmp, audioPath);

		data += tmp;

		try {
			this->socket->send_to(boost::asio::buffer(data), this->serverEndpoint);
		}
		catch (std::exception& e) {
			e.what();
		}

		}));
}

