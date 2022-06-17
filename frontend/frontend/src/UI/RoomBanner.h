#pragma once
#include <Siv3D.hpp>

class RoomBanner {
private:
	//
public:

	int32 margin = 8;
	int32 width = 400;
	int32 height = 150;
	String name;
	int32 members;
	Rect rect;
	Transition tss = Transition(0.2s, 0.3s);

	RoomBanner(const String& name, const int32 members)
		: name(name), members(members)
	{
		rect = Rect(width, height);
	}

	void update()
	{
		tss.update(rect.mouseOver());

		if (rect.mouseOver())
		{
			Cursor::RequestStyle(CursorStyle::Hand);
		}
	}

	bool sceneChange()
	{
		return rect.leftClicked();
	}

	void draw(const Point& origin, const int32& i) const
	{
		//
	}
};
