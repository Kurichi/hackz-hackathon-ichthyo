#include "stdafx.h"
#include "Core/Audio/UserVoiceRecorder.h"
#include "Core/User.h"
#include <format>
#include "Core/Util.h"

using namespace boost::asio::ip;

UserVoiceRecorder::UserVoiceRecorder(const udp::endpoint& serverEndpoint) :
	tmpAudioFileDirectory("tmpAudio"),
	previousSendedTime(0),
	recorder(1s, Loop::Yes, StartImmediately::Yes),
	serverEndpoint(serverEndpoint),
	socket(SingletonSocket::Get())
{
	this->recorder.SetMicrophoneRecordDuration(1s);
}

void UserVoiceRecorder::SendAudioData(const User& myUser ) {
	static std::unique_ptr<std::thread> sendAudioThreadPtr = nullptr;
	if (this->previousSendedTime + 1 > Scene::Time()) {
		double hoge = Scene::Time();

		return;
	}
	previousSendedTime = Scene::Time();
	Wave wave = recorder.GetRecentWave();
	if (sendAudioThreadPtr != nullptr)
	{
		sendAudioThreadPtr->join();
	}

	sendAudioThreadPtr.reset(new std::thread([wave, myUser, this] {
		const std::string audioPath = (this->tmpAudioFileDirectory / "hoge.ogg").string();
		if (!wave.save(Unicode::Widen(audioPath))) {
			return;
		}

		std::string data = std::format("{}\n{}\n{}\n{}\n", myUser.name, myUser.uuid, 0, 1);
		std::string tmp;

		Util::ReadBinary(tmp, audioPath);

		data += tmp;

		this->socket->send(boost::asio::buffer("name\nid\n0\n1\n" + tmp));

		}));
}

