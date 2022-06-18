#include "stdafx.h"
#include "Core/Audio/UserVoiceRecorder.h"
#include "Core/User.h"
#include <format>
#include "Core/Util.h"

using namespace boost::asio::ip;

UserVoiceRecorder::UserVoiceRecorder(const udp::endpoint& serverEndpoint, const User &User) :
	tmpAudioFileDirectory("tmpAudio"),
	previousSendedTime(0),
	recorder(),
	serverEndpoint(serverEndpoint),
	socket(SingletonSocket::Get()),
	sock(ios, udp::endpoint(address::from_string("127.0.0.1"), 32153)),
	myUser(User)
{
	SendVoice.reset(new std::thread([&] {
		while (true) {
			if (!this->VoiceQueue.empty()) {
				boost::asio::io_service io_service;
				Wave wave = VoiceQueue.front();
				this->VoiceQueue.pop();
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
			}
		}
		}));
	this->recorder.SetMicrophoneRecordDuration(1s);
}

void UserVoiceRecorder::SendAudioData() {

	previousSendedTime += Scene::DeltaTime();
	if (this->previousSendedTime < 0.998) {
		return;
	}
	previousSendedTime = 0;
	Wave wave = recorder.GetRecentWave();
	VoiceQueue.push(wave);

}
