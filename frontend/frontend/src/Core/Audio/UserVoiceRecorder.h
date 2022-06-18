#pragma once
#include <filesystem>
#include <boost/asio.hpp>
#include <memory>
#include "Core/User.h"
#include "Core/Audio/Recorder.h"
#include "Core/Connection/SingletonSocket.h"

class UserVoiceRecorder {
private:
	const std::filesystem::path tmpAudioFileDirectory;
	boost::asio::io_service io_service;
	Recorder recorder;
	double previousSendedTime;
	boost::asio::ip::udp::endpoint serverEndpoint;
	std::shared_ptr<boost::asio::ip::udp::socket> socket;
	boost::asio::io_service ios;
	boost::asio::ip::udp::socket sock;
	std::queue<Wave> VoiceQueue;
	std::unique_ptr<std::thread> SendVoice;
	const User& myUser;
public:
	UserVoiceRecorder(const boost::asio::ip::udp::endpoint& serverEndpoint, const User& myUser);
	void SendAudioData();
};

