#pragma once
#include <Siv3D.hpp>

// 名前設定用モーダルクラス

class NameSetModal {
private:

	Font font = Font(30);
	String text;
	Rect rect;
	s3d::RoundRect rrect;

public:

	bool show = 0;

	// コンストラクタ
	const NameSetModal()
	{
		rect = Rect(
			Scene::Center().x, 300,
			int(Scene::Width() * 0.7), 400
		);
		rrect = s3d::RoundRect(rect, 10);
	}

	// 更新
	void update(const bool u)
	{
		TextInput::UpdateText(text);
	}

	// 描画
	void draw() const
	{
		rrect.draw(ColorF(1.0));
		font(text).draw(rect.stretched(-20));
	}
};

/*

To Do
・名前変更モーダルの実装
・発言者のソート(線形補完でアニメーション)
(・アイコン変更モーダルの実装(テンプレ))

*/
