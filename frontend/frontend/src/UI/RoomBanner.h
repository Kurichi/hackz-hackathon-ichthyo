#pragma once
#include <Siv3D.hpp>
#include "JoinButton.h"

// 部屋一覧シーンに用いる部屋バナークラス
class RoomBanner {
private:
	int32 margin = 8;
	int32 width;
	int32 height = 150;
	int32 index;
	int32 centerY;
	String name;
	int32 members;
	Rect rect;
	JoinButton btn;
	Transition tss = Transition(0.2s, 0.3s);
public:

	// コンストラクタ
	// 引数 : 部屋名, 人数, 幅, 添字
	RoomBanner(const String& name, const int32& members, const int32& width, const int32 index)
		: name(name), members(members), width(width), index(index)
	{
		rect = Rect(width, height);
		btn = JoinButton();
	}

	// 毎フレームの更新
	void update()
	{
		tss.update(rect.mouseOver());

		// ボタンのマウスオーバー時, カーソルを変更する
		btn.update();
	}

	bool sceneChange()
	{
		return rect.leftClicked();
	}

	void draw(const Point& origin, const int32& i) const
	{
		btn.draw();
	}
};
