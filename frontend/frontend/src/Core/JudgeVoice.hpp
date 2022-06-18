#pragma once

#include <Siv3D.hpp>

//JudgeVoice::judgetype 判断基準の定義
#define AVE_AMP 0x1     //振幅の平均
#define PITCH 0x2

class JudgeVoice {
public:
	JudgeVoice(int type_ = AVE_AMP);
	void SetThre(int type_, double thre_); //type_のタイプのしきい値の設定
	void SetType(int type_);               //判断タイプの設定
	bool Judge(Microphone& mic);           //実際に判定してtrue,falseを返す
	double GetAveAmp(FFTResult fft);       //平均音量を得る
	double GetPitch(FFTResult fft);        //音高を得る
private:
	bool JudgeforAveAmp(FFTResult fft);    //amp_threに基づいて音量判断
	bool JudgeforPitch(FFTResult fft);     //pitch_threに基づいて音高判断
	int judgetype;                         //判断タイプ
	double amp_thre;                       //音量のしきい値
	double pitch_thre;                     //音高のしきい値
};