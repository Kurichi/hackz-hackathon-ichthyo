#include "Core/JudgeVoice.hpp"
#include <Siv3D.hpp>

JudgeVoice::JudgeVoice(int type_) {
	amp_thre = 0.005;
	pitch_thre = 1000;
	SetType(type_);
}

void JudgeVoice::SetThre(int type_, double thre_) {
	if (type_ & AVE_AMP) amp_thre = thre_;
	if (type_ & PITCH) pitch_thre = thre_;
	return;
}
void JudgeVoice::SetType(int type_) {
	judgetype = type_;
	if ((type_ & AVE_AMP) != 0) amp_thre = 0.005;
	if ((type_ & PITCH) != 0) pitch_thre = 1000;
	if ((type_ & L_AVE_AMP) != 0) amp_thre = 0.002;
	if ((type_ & L_PITCH) != 0) pitch_thre = 400;

}

bool JudgeVoice::Judge(Microphone mic) {
	FFTResult fft;
	mic.fft(fft);

	bool aveamp = true;
	bool pitch = true;
	bool laveamp = true;
	bool lpitch = true;

	if ((judgetype & AVE_AMP) != 0)
		aveamp = JudgeforAveAmp(fft);
	if ((judgetype & PITCH) != 0)
		pitch = JudgeforPitch(fft);
	if ((judgetype & L_AVE_AMP) != 0)
		laveamp = !JudgeforAveAmp(fft);
	if ((judgetype & L_PITCH) != 0)
		lpitch = !JudgeforPitch(fft);


	bool ret = aveamp && pitch && laveamp && lpitch;

	return ret;
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
	double max1 = 0, max2 = 0, max3 = 0;
	int max_num1 = 0, max_num2 = 0, max_num3 = 0;

	for (int i = 0; i < 800; i++) {
		if (fft.buffer[i] > max1) {
			max3 = max2;
			max2 = max1;
			max1 = fft.buffer[i];

			max_num3 = max_num2;
			max_num2 = max_num1;
			max_num1 = i;
		}
	}

	double ret = 0;
	ret += max1 / (max1 + max2 + max3) * max_num1 * fft.resolution;
	ret += max2 / (max1 + max2 + max3) * max_num2 * fft.resolution;
	ret += max3 / (max1 + max2 + max3) * max_num3 * fft.resolution;
	return ret;
}

bool JudgeVoice::JudgeforPitch(FFTResult fft) {

	if (GetPitch(fft) > pitch_thre) return true;
	return false;
}

bool JudgeVoice::JudgeforAveAmp(FFTResult fft) {
	double ave = GetAveAmp(fft);

	if (ave > amp_thre) return true;
	else return false;
}