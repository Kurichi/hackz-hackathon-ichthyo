#pragma once

#include <Siv3D.hpp>
#include <filesystem>

class Recorder {
private:
	bool microphoneRecordDurationSetFlag;
	Microphone microphone;
	SecondsF microphoneRecordDuration;
public:
	template <class ...Args>
	Recorder(Args ...args) :
		microphoneRecordDurationSetFlag(false),
		microphone(args...),
		microphoneRecordDuration()
	{}

	Recorder();
	Recorder(const Microphone& mic);
	void SetMicrophoneRecordDuration(const SecondsF& duration);
	void SetMicrophone(const Microphone& mic);
	Wave GetRecentWave() const;
	bool SaveRecentWave(const std::filesystem::path& path)const;
	SecondsF GetMicrophoneRecordDuration() const {
		return microphoneRecordDuration;
	}
};



