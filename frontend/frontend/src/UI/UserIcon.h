#pragma once
#include <Siv3D.hpp>

// ユーザーのアイコン等

class UserIcon {
private:
	int32 userID = 0;
	ColorF color = ColorF(1.0);
	String name = U"名無し";
	Texture img;
	int32 radius = 80;
	Circle circle;
	Point center;
	const Font font = Font(20);
	double volume;
public:

	const static int32 width = 200;
	const static int32 height = 250;

	// コンストラクタ
	UserIcon(const int32& userID, const ColorF color, const String& name)
		: userID(userID), color(color), name(name)
	{
		img = Texture(color);
	}

	// volumeの更新
	void update(const double& volume, const Point& center)
	{
		this->volume = volume;
		this->center = center;
		circle = Circle(0, 0, radius).movedBy(center);
	}

	// 描画
	void draw() const
	{
		circle.draw();
		// テクスチャの (85, 0) から幅 120 高さ 120 の領域を、circle に貼り付けて描画
		circle(img(85, 0, 120, 120)).draw();
		font(name).draw(Arg::center = center.movedBy(0, radius + 30), Palette::Black);
		circle.stretched(5).drawArc(0, Math::Pi * 2 * volume, 0, 10, ColorF(1.0, 1.0 - volume, 1.0 - volume));
		if (volume < 1.0) {
			circle.draw(ColorF(0.0, 0.7));
		}
	}
};
