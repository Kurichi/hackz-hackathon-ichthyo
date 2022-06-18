#include "Core/JudgeVoice.hpp"
#include <Siv3D.hpp>

JudgeVoice::JudgeVoice(int type_) {
	judgetype = type_;
}

void JudgeVoice::SetThre(int type_, double thre_) {
	if (type_ & AVE_AMP) amp_thre = thre_;
	if (type_ & PITCH) pitch_thre = thre_;
	return;
}
void JudgeVoice::SetType(int type_) {
	judgetype = type_;
}

bool JudgeVoice::Judge(Microphone& mic) {
	FFTResult fft;
	mic.fft(fft);

	bool aveamp = true;
	bool pitch = true;

	if ((judgetype & AVE_AMP) != 0)
		aveamp = JudgeforAveAmp(fft);
	if ((judgetype & PITCH) != 0)
		pitch = JudgeforPitch(fft);

	bool ret = aveamp && pitch;

	return ret;
}

bool JudgeVoice::JudgeforAveAmp(FFTResult fft) {
	double ave = GetAveAmp(fft);

	if (ave >= amp_thre) return true;
	else return false;
}

double JudgeVoice::GetAveAmp(FFTResult fft) {
	double ave = 0;
	int c = 0;

	for (auto i : step(800)) {
		ave += fft.buffer[i];
		c++;
	}

	ave /= c;

	return ave;
}

double JudgeVoice::GetPitch(FFTResult fft) {
	double max = 0;
	int max_num = 0;

	for (auto i : step(800)) {
		if (fft.buffer[i] > max) {
			max = fft.buffer[i];
			max_num = i;
		}
	}

	return max_num * fft.resolution;
}

bool JudgeVoice::JudgeforPitch(FFTResult fft) {

	if (GetPitch(fft) > pitch_thre) return true;
	return false;
}
