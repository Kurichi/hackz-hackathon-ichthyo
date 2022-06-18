#pragma once

#include <Siv3D.hpp>

//JudgeVoice::judgetype ���f��̒�`
#define AVE_AMP 0x1     //�U���̕���
#define PITCH 0x2

class JudgeVoice {
public:
	JudgeVoice(int type_ = AVE_AMP);
	void SetThre(int type_, double thre_); //type_�̃^�C�v�̂������l�̐ݒ�
	void SetType(int type_);               //���f�^�C�v�̐ݒ�
	bool Judge(Microphone& mic);           //���ۂɔ��肵��true,false��Ԃ�
	double GetAveAmp(FFTResult fft);       //���ω��ʂ𓾂�
	double GetPitch(FFTResult fft);        //�����𓾂�
private:
	bool JudgeforAveAmp(FFTResult fft);    //amp_thre�Ɋ�Â��ĉ��ʔ��f
	bool JudgeforPitch(FFTResult fft);     //pitch_thre�Ɋ�Â��ĉ������f
	int judgetype;                         //���f�^�C�v
	double amp_thre;                       //���ʂ̂������l
	double pitch_thre;                     //�����̂������l
};