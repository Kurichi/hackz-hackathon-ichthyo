#pragma once
#include <Siv3D.hpp>

// マイク等のボタン

class ToggleButton {
private:
	int32 code;
	Texture img;
	int32 x;
	int32 y;
	int32 radius;
	Circle circle;
	bool boolean;
	Transition tss;
public:

	const static int32 width = 200;
	const static int32 height = 250;

	// コンストラクタ
	const ToggleButton() {};
	const ToggleButton(const int32& code, const int32& x, const int32& y, const int32& radius)
		: code(code), x(x), y(y), radius(radius)
	{
		circle = Circle(x, y, radius);
		img = Texture(Icon(code), radius * 2);
	}

	// 更新
	void update(const bool& boolean)
	{
		this->boolean = boolean;
		tss.update(circle.mouseOver());
		if(circle.mouseOver())Cursor::RequestStyle(CursorStyle::Hand);
	}

	bool leftClicked() {
		return circle.leftClicked();
	}

	// 描画
	void draw() const
	{
		circle.draw(ColorF(0.4, 0.4, 1.0, tss.value()));
		img.scaled(0.6).drawAt(x, y);
	}
};
