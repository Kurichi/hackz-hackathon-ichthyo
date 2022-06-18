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
	
public:
	UserVoiceRecorder(const boost::asio::ip::udp::endpoint& serverEndpoint);
	void SendAudioData(const User& myUser);
};

