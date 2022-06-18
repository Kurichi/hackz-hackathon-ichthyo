#pragma once

#include <Siv3D.hpp>
#include <filesystem>

class Recorder {
private:
	bool microphoneRecordDurationSetFlag;
	std::shared_ptr<Microphone> microphone;
	SecondsF microphoneRecordDuration;
public:
	Recorder();
	void SetMicrophoneRecordDuration(const SecondsF& duration);
	Wave GetRecentWave() const;
	bool SaveRecentWave(const std::filesystem::path& path)const;
	SecondsF GetMicrophoneRecordDuration() const {
		return microphoneRecordDuration;
	}
};



