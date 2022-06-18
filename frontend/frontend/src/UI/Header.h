#pragma once
#include <Siv3D.hpp>
// 上部のメニュー

class Header {
private:
	//
public:

	// コンストラクタ
	Header()
	{
		//
	}

	// 毎フレームの更新
	void update()
	{
		//
	}

	// 描画
	void draw() const
	{
		Rect(
			Arg::center = Point(Scene::Center().x, 40),
			Scene::Width(), 80
		).draw(ColorF(0.0, 0.0, 1.0));
	}
};
