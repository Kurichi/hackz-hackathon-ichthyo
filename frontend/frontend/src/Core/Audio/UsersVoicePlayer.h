#pragma once
#include <vector>
#include <string>
#include <filesystem>
#include <boost/asio.hpp>
#include <unordered_map>
#include "Core/Connection/UDPReceiver.h"
#include "Core/Util.h"

class UsersVoicePlayer {
private:
	UDPReceiver udpReceiver;
	boost::asio::ip::udp::endpoint serverEndpoint;
	const std::filesystem::path receivedAudioPath;
	bool continueFlag;
	bool speakerMuteFlag;
	std::unordered_map<std::string, Audio> audioUUIDMap;
public:
	UsersVoicePlayer(
		boost::asio::ip::udp::endpoint serverEndpoint);
	void ReceiveAndPlayLoop();
	bool IsUserAudioPlaying(const std::string& uuid) const;
	bool ToggleSpeakerMute();
	bool IsSpeakerMute();
	void StopLoop() {
		continueFlag = false;
	}
};