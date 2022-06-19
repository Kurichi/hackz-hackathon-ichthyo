#pragma once
#include <Siv3D.hpp>
#include "Scene.h"
#include "Header.h"
#include "NameSetModal.h"
#include "UserIcon.h"
#include "Core/Audio/SingletonMicrophone.h"
#include "Core/JudgeVoice.hpp"
#include "Core/User/SingletonUserArray.h"

extern JudgeVoice jv;

extern User me;

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
		auto userArray = SingletonUserArray::Get();
		// 更新があったときにも update 関数内で読み込む
		usericons.clear();
		for (auto i : step(userArray->size())) {
			usericons << UserIcon(
				(*userArray)[i].iconIndex,
				Unicode::Widen((*userArray)[i].name)
			);
		}

		// マイク関連
		mic = SingletonMicrophone::Get();
		mic->fft(fft);
	}

	void update() override
	{

		auto userArray = SingletonUserArray::Get();
		for (int i = usericons.size(); i < userArray->size(); i++) {
			usericons << UserIcon(
				(*userArray)[i].iconIndex,
				Unicode::Widen((*userArray)[i].name)
			);
		}
		for (auto i : step(userArray->size())) {
			usericons[i].setName(Unicode::Widen((*userArray)[i].name));
		}
		
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
		nsm.update(header.nameLeftClicked());

		// sIn, sOutの更新
		if (header.update_sIn()) getData().sIn ^= 1;
		if (header.update_sOut()) getData().sOut ^= 1;

		// fft更新
		mic->fft(fft);
	}

	void draw() const override
	{
		//auto userArray = SingletonUserArray::Get();
		//User* hoge = SingletonUserArray::Search(me);
		// ユーザアイコンの描画
		for (auto i : step(usericons.size())) {
			usericons[i].draw();
		}

		// ヘッダの描画
		header.draw();
	}

};
