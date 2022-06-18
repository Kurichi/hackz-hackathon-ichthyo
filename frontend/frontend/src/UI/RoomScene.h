#pragma once
#include <Siv3D.hpp>
#include "Scene.h"
#include "Header.h"
#include "UserIcon.h"

// 部屋シーン(ここで通話する)
class Room : public MyApp::Scene
{
private:

	Header header;
	Array<UserIcon> usericons;
	int32 w;
	int32 scrollY = 0;

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
		header.draw();
	}

};
