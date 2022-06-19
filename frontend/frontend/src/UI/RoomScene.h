#pragma once
#include <Siv3D.hpp>
#include "Scene.h"
#include "Header.h"
#include "NameSetModal.h"
#include "UserIcon.h"
#include "Core/Audio/SingletonMicrophone.h"
#include "Core/JudgeVoice.hpp"

extern JudgeVoice jv;

// 部屋シーン(ここで通話する)
class Room : public MyApp::Scene
{
private:

	Header header;
	NameSetModal nsm;
	Array<UserIcon> usericons;
	int32 w;
	int32 scrollY = 0;
	std::shared_ptr<s3d::Microphone> mic;
	FFTResult fft;

public:

	// コンストラクタ
	Room(const InitData& init) : IScene(init)
	{
		// ここでユーザ情報を読み込む
		// 更新があったときにも update 関数内で読み込む
		header = Header(
			getData().currentUserID,
			getData().srclist[getData().currentUserID],
			getData().namelist[getData().currentUserID]
		);
		usericons.clear();
		for (auto i : step(getData().namelist.size())) {
			usericons << UserIcon(
				i,
				getData().srclist[i],
				getData().namelist[i]
			);
		}

		// マイク関連
		mic = SingletonMicrophone::Get();
		mic->fft(fft);
	}

	void update() override
	{
		// ヘッダの更新
		header.update(getData().sIn, getData().sOut);

		// ユーザアイコンを横に何列描画するか決める．
		w = Scene::Width() / UserIcon::width;

		// スクロール
		scrollY += Mouse::Wheel() * 50;
		scrollY = Max(0, scrollY);
		scrollY = Min(scrollY, int32(UserIcon::height * (usericons.size() / w - 1)));

		// ユーザアイコンの位置・装飾更新
		for (auto i : step(usericons.size())) {
			usericons[i].update(
				jv.GetAveAmp(fft) / 0.004,
				Scene::Center().movedBy(
					UserIcon::width * (i % w - w / 2.0 + 0.5),
					UserIcon::height * (i / w) - scrollY - 100
				)
			);
		}

		// 名前クリック時にnsm表示．
		//nsm.update()

		// sIn, sOutの更新
		if (header.update_sIn()) getData().sIn ^= 1;
		if (header.update_sOut()) getData().sOut ^= 1;

		// fft更新
		mic->fft(fft);
	}

	void draw() const override
	{
		// ユーザアイコンの描画
		for (auto i : step(usericons.size())) {
			usericons[i].draw();
		}

		// ヘッダの描画
		header.draw();
	}

};
