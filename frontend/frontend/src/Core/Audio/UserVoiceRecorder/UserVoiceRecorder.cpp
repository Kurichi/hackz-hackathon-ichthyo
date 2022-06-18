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
{}

void UserVoiceRecorder::SendAudioData(const User& myUser ) {
	static auto sendAudioThreadPtr = std::make_unique<std::thread>();
	if (this->previousSendedTime + this->recorder.GetMicrophoneRecordDuration().count() > Scene::Time()) return;
	Wave wave = recorder.GetRecentWave();
	if (sendAudioThreadPtr != nullptr) sendAudioThreadPtr->join();

	sendAudioThreadPtr.reset(new std::thread([wave, myUser, this] {
		const std::string audioPath = (this->tmpAudioFileDirectory / "hoge.ogg").string();
		if (!wave.save(Unicode::Widen(audioPath))) {
			return;
		}

		std::string data = std::format("{}\n{}\n{}\n{}\n", myUser.name, myUser.uuid, 0, 1);
		std::string tmp;

		Util::ReadBinary(tmp, audioPath);

		data += tmp;

		this->socket->send_to(boost::asio::buffer(data), this->serverEndpoint);
		}));
}

