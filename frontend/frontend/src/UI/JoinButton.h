#pragma once
#include <Siv3D.hpp>

// 部屋バナーに用いる参加ボタンクラス
class JoinButton {
private:
	int32 width = 100;
	int32 height = 60;
	int32 radius = 8;
	RoundRect rrect;
	Line arrow;
	Transition tss = Transition(0.2s, 0.3s);
public:

	// コンストラクタ
	JoinButton() {};
	// 引数 : 中心
	JoinButton(Point& origin)
	{
		rrect = RoundRect(
			Rect(Arg::center = origin, width, height),
			radius
		);
		arrow = Line(
			Point(-width / 2, 0),
			Point(width / 2, 0)
		).moveBy(origin);
	}

	// 毎フレームの更新
	void update()
	{
		tss.update(rrect.mouseOver());

		// マウスオーバー時, カーソルを変更する
		if (rrect.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}
	}

	void draw() const
	{
		rrect.draw(Color(0.1, 0.6, 1.0));
	}
};
