﻿#include "stdafx.h"
#include "Core/Audio/UsersVoicePlayer.h"
#include "Core/Connection/UDPReceiver.h"
#include "Core/Util.h"


UsersVoicePlayer::UsersVoicePlayer(
	boost::asio::ip::udp::endpoint serverEndpoint
) :
	receivedAudioPath("receivedAudio"),
	udpReceiver(),
	serverEndpoint(serverEndpoint),
	continueFlag(true)
{}

void UsersVoicePlayer::ReceiveAndPlayLoop() {
	while (this->continueFlag) {
		std::string data = this->udpReceiver.Receive();
		
		Util::ReceivedData recvData{ data };

		const std::string audioPath = std::format("{}/{}.ogg", this->receivedAudioPath.string(), recvData.user.uuid);

		Util::CreateWav(audioPath,recvData.data	);

		if (this->audioUUIDMap.count(recvData.user.uuid)) {
			this->audioUUIDMap.at(recvData.user.uuid) = Audio(Unicode::Widen(audioPath));
		}
		else {
			this->audioUUIDMap.emplace(recvData.user.uuid, Audio(Unicode::Widen(audioPath)));
		}
		if (!this->audioUUIDMap.at(recvData.user.uuid)) continue;
		this->audioUUIDMap.at(recvData.user.uuid).play();
	}
}

bool UsersVoicePlayer::IsUserAudioPlaying(const std::string& uuid) const{
	return this->audioUUIDMap.at(uuid).isPlaying();
}
