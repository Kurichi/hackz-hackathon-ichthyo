#include "stdafx.h"
#include "Core/Audio/UsersVoicePlayer.h"
#include "Core/Connection/UDPReceiver.h"
#include "Core/Util.h"

//src/UI/roomscene.h
extern bool spe_mute;


UsersVoicePlayer::UsersVoicePlayer(
	boost::asio::ip::udp::endpoint serverEndpoint
) :
	receivedAudioPath("receivedAudio"),
	udpReceiver(),
	serverEndpoint(serverEndpoint),
	continueFlag(true),
	speakerMuteFlag(false)
{}

void UsersVoicePlayer::ReceiveAndPlayLoop() {
	while (this->continueFlag) {
		std::string data = this->udpReceiver.Receive();

		if (this->speakerMuteFlag) {
			continue;
		}
		
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
		this->audioUUIDMap.at(recvData.user.uuid).setVolume(1);
		if(spe_mute) this->audioUUIDMap.at(recvData.user.uuid).playOneShot();
	}
}

bool UsersVoicePlayer::IsSpeakerMute() {
	return this->speakerMuteFlag;
}

bool UsersVoicePlayer::IsUserAudioPlaying(const std::string& uuid) const{
	return this->audioUUIDMap.at(uuid).isPlaying();
}

bool UsersVoicePlayer::ToggleSpeakerMute() {
	this->speakerMuteFlag = !(this->speakerMuteFlag);
	return this->speakerMuteFlag;
}
