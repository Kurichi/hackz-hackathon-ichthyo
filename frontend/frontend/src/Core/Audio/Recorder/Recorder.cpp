#include "Core/Audio/Recorder.h"
#include <filesystem>

namespace filesystem = std::filesystem;

	Recorder::Recorder() :
		microphoneRecordDurationSetFlag(true),
		microphone(),
		microphoneRecordDuration(microphone.DefaultBufferDuration)
	{}

	Recorder::Recorder(const Microphone& mic) :
		microphoneRecordDurationSetFlag(false),
		microphone(mic),
		microphoneRecordDuration()
	{}

	void Recorder::SetMicrophoneRecordDuration(const SecondsF& duration) {
		this->microphoneRecordDuration = duration;
		this->microphoneRecordDurationSetFlag = true;
	}

	void Recorder::SetMicrophone(const Microphone& mic) {
		this->microphone = mic;
	}

	Wave Recorder::GetRecentWave() const {
		return this->microphone.getBuffer();
	}

	bool Recorder::SaveRecentWave(const filesystem::path& path) const {
		if (!filesystem::exists(path.parent_path())) {
			return false;
		}
		return this->microphone.getBuffer().save(Unicode::Widen(path.string()));
	}
