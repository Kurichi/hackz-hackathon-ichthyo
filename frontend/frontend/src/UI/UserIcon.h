#pragma once
#include <Siv3D.hpp>

// ユーザーのアイコン等

class UserIcon {
private:
	Texture img;
	String name;
	int32 radius = 80;
	Circle circle;
	Point center;
	const Font font = Font(20);
	double volume;
public:

	const static int32 width = 200;
	const static int32 height = 250;

	// コンストラクタ
	UserIcon(const String& src, const String& name)
		: name(name)
	{
		img = Texture(src, TextureDesc::Mipped);
	}

	// volumeの更新
	void update(const double& volume, const Point& center)
	{
		this->center = center;
		circle = Circle(0, 0, radius).movedBy(center);
	}

	// 描画
	void draw() const
	{
		// テクスチャの (85, 0) から幅 120 高さ 120 の領域を、circle に貼り付けて描画
		circle(img(85, 0, 120, 120)).draw();
		font(name).draw(Arg::center = center.movedBy(0, radius + 30), Palette::Black);
	}
};
