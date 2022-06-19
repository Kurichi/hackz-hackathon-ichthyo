#include "Core/Audio/Recorder.h"
#include "Core/Audio/SingletonMicrophone.h"
#include <filesystem>

namespace filesystem = std::filesystem;

	Recorder::Recorder() :
		microphoneRecordDurationSetFlag(false),
		microphone(SingletonMicrophone::Get()),
		microphoneRecordDuration()
	{}


	void Recorder::SetMicrophoneRecordDuration(const SecondsF& duration) {
		this->microphoneRecordDuration = duration;
		this->microphoneRecordDurationSetFlag = true;
	}


	Wave Recorder::GetRecentWave() const {
		return this->microphone->getBuffer();
	}

	bool Recorder::SaveRecentWave(const filesystem::path& path) const {
		if (!filesystem::exists(path.parent_path())) {
			return false;
		}
		return this->microphone->getBuffer().save(Unicode::Widen(path.string()));
	}
