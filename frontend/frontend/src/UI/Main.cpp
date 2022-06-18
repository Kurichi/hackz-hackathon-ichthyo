#include <Siv3D.hpp> // OpenSiv3D v0.6.3
#include "RoomBanner.h"

// シーンの名前
enum class State
{
	Roomlist,
	Room
};

// シーン間で共有するデータ
struct Data
{
	int roomidx = 0;
};

// シーン管理クラス
using MyApp = SceneManager<State, Data>;

// 部屋一覧シーン
class Roomlist : public MyApp::Scene
{
private:

	Array<RoomBanner> roombanners;
	Point origin;
	int32 scrolly = 0;

public:

	Roomlist(const InitData& init) : IScene(init) {
		roombanners << RoomBanner(U"名無しの部屋", 1);
	}

	void update() override
	{
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

// 部屋シーン
class Room : public MyApp::Scene
{
private:

	Array<Rect> btns_var;
	Array<Triangle> tris_var;
	Array<Transition> tsss_var;

	Rect btn_start = Rect(Arg::center = Scene::Center().movedBy(0, 130), 600, 100);
	Transition tss_start = Transition(0.2s, 0.1s);

	Rect btn_exit = Rect(Arg::center = Scene::Center().movedBy(0, 260), 600, 100);
	Transition tss_exit = Transition(0.2s, 0.1s);

public:

	Room(const InitData& init) : IScene(init)
	{
		//
	}

	void update() override
	{
		//
	}

	void draw() const override
	{
		//
	}

};

void Main()
{
	// 使用するフォントアセットを登録
	FontAsset::Register(U"Title", 120, Typeface::Bold);


	// シーンサイズの変更
	Scene::Resize(800, 800);
	// 全画面にしない
	if (false) Window::SetFullscreen(true);
	// 手動リサイズを許可する
	else Window::SetStyle(WindowStyle::Sizable);

	// 背景の色を設定 | Set background color
	Scene::SetBackground(ColorF{ 1.0, 1.0, 1.0 });

	// シーンと遷移時の色を設定
	MyApp manager;
	manager
		.add<Roomlist>(State::Roomlist)
		.add<Room>(State::Room)
		.setFadeColor(ColorF{ 0.0, 0.0, 0.0 });

	while (System::Update())
	{
		if (!manager.update())
		{
			break;
		}
	}
}

//
// = アドバイス =
// Debug ビルドではプログラムの最適化がオフになります。
// 実行速度が遅いと感じた場合は Release ビルドを試しましょう。
// アプリをリリースするときにも、Release ビルドにするのを忘れないように！
//
// 思ったように動作しない場合は「デバッグの開始」でプログラムを実行すると、
// 出力ウィンドウに詳細なログが表示されるので、エラーの原因を見つけやすくなります。
//
// = お役立ちリンク | Quick Links =
//
// Siv3D リファレンス
// https://zenn.dev/reputeless/books/siv3d-documentation
//
// Siv3D Reference
// https://zenn.dev/reputeless/books/siv3d-documentation-en
//
// Siv3D コミュニティへの参加
// Slack や Twitter, BBS で気軽に質問や情報交換ができます。
// https://zenn.dev/reputeless/books/siv3d-documentation/viewer/community
//
// Siv3D User Community
// https://zenn.dev/reputeless/books/siv3d-documentation-en/viewer/community
//
// 新機能の提案やバグの報告 | Feedback
// https://github.com/Siv3D/OpenSiv3D/issues
//
