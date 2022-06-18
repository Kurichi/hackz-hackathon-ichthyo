#pragma once
#include <Siv3D.hpp>
#include "Scene.h"
#include "RoomBanner.h"

// 部屋一覧シーン
class Roomlist : public MyApp::Scene
{
private:

	Array<RoomBanner> roombanners;
	Point origin;
	int32 scrolly = 0;

public:

	Roomlist(const InitData& init) : IScene(init) {
		// ここで部屋のリストを読み込む
		roombanners << RoomBanner(U"名無しの部屋", 1, Scene::Width()*0.8, 0);
	}

	void update() override
	{
		// 部屋のリストに関する更新
		for (auto i : step(roombanners.size())) {
			RoomBanner rb = roombanners[i];
			rb.update();
			if (rb.sceneChange()) {
				getData().roomidx = i;
				changeScene(State::Room, 0.3s);
			}
		}

		origin = Point(Scene::Center().x, 100 + scrolly);

		/*
		tss_start.update(btn_start.mouseOver());
		tss_exit.update(btn_exit.mouseOver());

		if (btn_start.mouseOver() || btn_exit.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}

		if (btn_start.leftClicked())
		{
			changeScene(State::Room, 0.3s);
		}

		if (btn_exit.leftClicked())
		{
			System::Exit();
		}
		*/
	}

	void draw() const override
	{
		// 部屋のリストに関する描画
		for (auto i : step(roombanners.size()))roombanners[i].draw(origin, i);

		/*
		const String titleText = U"Maze";
		//FontAsset(U"Title")(titleText).drawAt(Scene::Center().movedBy(0, -200), ColorF(0.0, 0.5, 0.8));
		FontAsset(U"Title")(titleText).drawAt(Scene::Center().movedBy(0, -200));

		btn_start.draw(ColorF(1.0, tss_start.value())).drawFrame(2);
		btn_exit.draw(ColorF(1.0, tss_exit.value())).drawFrame(2);

		FontAsset(U"Menu")(U"START").drawAt(btn_start.center(), HSV(240.0, tss_start.value(), 1.0 - tss_start.value() / 3));
		FontAsset(U"Menu")(U"EXIT").drawAt(btn_exit.center(), HSV(240.0, tss_exit.value(), 1.0 - tss_exit.value() / 3));
		*/
	}
};
