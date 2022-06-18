#pragma once
#include <Siv3D.hpp>
#include "Scene.h"
#include "Header.h"
#include "UserIcon.h"

// 部屋シーン(ここで通話する)
class Room : public MyApp::Scene
{
private:

	Array<UserIcon> usericons;
	int32 w;
	int32 scrollY = 0;

public:

	// コンストラクタ
	Room(const InitData& init) : IScene(init)
	{
		// ここでユーザリストを読み込む
		// 更新があったときにも update 関数内で読み込む
		usericons.clear();
		usericons << UserIcon(U"example/siv3d-kun.png", U"名無し0");
		usericons << UserIcon(U"example/siv3d-kun.png", U"名無し1");
		usericons << UserIcon(U"example/siv3d-kun.png", U"名無し2");
		usericons << UserIcon(U"example/siv3d-kun.png", U"名無し3");
		usericons << UserIcon(U"example/siv3d-kun.png", U"名無し4");
		usericons << UserIcon(U"example/siv3d-kun.png", U"名無し5");
		usericons << UserIcon(U"example/siv3d-kun.png", U"名無し6");
	}

	void update() override
	{
		// 横に何列描画するか決める．
		w = Scene::Width() / UserIcon::width;

		// スクロール
		scrollY += Mouse::Wheel() * 50;
		scrollY = Max(0, scrollY);
		scrollY = Min(scrollY, int32(UserIcon::height * (usericons.size() / w - 1)));

		// ユーザアイコンの位置指定
		for (auto i : step(usericons.size())) {
			usericons[i].update(
				Random(),
				Scene::Center().movedBy(
					UserIcon::width * (i % w - w / 2.0 + 0.5),
					UserIcon::height * (i / w) - scrollY - 100
				)
			);
		}
	}

	void draw() const override
	{
		// ユーザアイコンの描画
		for (auto i : step(usericons.size())) {
			usericons[i].draw();
		}

		// ヘッダの描画
		Header().draw();
	}

};
