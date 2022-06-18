//# include <Siv3D.hpp> // OpenSiv3D v0.6.4
#include "Core/Audio/UsersVoicePlayer.h"
#include "Core/Connection/SingletonSocket.h"
#include "Core/Audio/UserVoiceRecorder.h"
#include "Core/User.h"

using namespace boost::asio::ip;
using namespace boost::asio;
//
//void Main()
//{
//	system("explorer .");
//	SingletonSocket::SetMyEndpoint(udp::endpoint(udp::v4(), 32153));
//	UserVoiceRecorder recorder(udp::endpoint(address::from_string("219.94.241.220"), 1234));
//
//	//UserVoiceRecorder recorder(udp::endpoint(ip::address::from_string("127.0.0.1"), 23236));
//	//SingletonSocket::SetMyEndpoint(udp::endpoint(udp::v4(), 32153));
//	//SingletonSocket::Get()->connect(udp::endpoint(ip::address::from_string("127.0.0.1"), 23236));
//	UsersVoicePlayer player(
//		udp::endpoint(boost::asio::ip::address::from_string("219.94.241.220"), 1234
//	));
//
//	std::thread playThread([&] {
//		player.ReceiveAndPlayLoop();
//		});
//		
//
//	
//	while (System::Update()){
//		recorder.SendAudioData({ "name", "1edfa37547" });
//		//recorder.SendAudioData({"name", "id"});
//		if (KeyLeft.pressed()) {
//			SingletonSocket::Get()->close();
//			std::this_thread::sleep_for(std::chrono::seconds(1));
//			return;
//		}
//
//
//		
//	}
//}

#include <Siv3D.hpp> // OpenSiv3D v0.6.3
#include "UI/Scene.h"// シーン管理等
//#include "RoomlistScene.h"// 部屋一覧シーン
#include "UI/RoomScene.h"// 部屋シーン(ここで通話する)

void Main()
{
	// 使用するフォントアセットを登録
	FontAsset::Register(U"Title", 120, Typeface::Bold);

	SingletonSocket::SetMyEndpoint(udp::endpoint(udp::v4(), 32153));
	UserVoiceRecorder recorder(udp::endpoint(address::from_string("219.94.241.220"), 1234), {"name", "1f1b33"});

	//UserVoiceRecorder recorder(udp::endpoint(ip::address::from_string("127.0.0.1"), 23236));
	//SingletonSocket::SetMyEndpoint(udp::endpoint(udp::v4(), 32153));
	//SingletonSocket::Get()->connect(udp::endpoint(ip::address::from_string("127.0.0.1"), 23236));
	UsersVoicePlayer player(
		udp::endpoint(boost::asio::ip::address::from_string("219.94.241.220"), 1234
		));

	std::thread playThread([&] {
		player.ReceiveAndPlayLoop();
		});



	// シーンサイズの変更
	//Scene::Resize(800, 800);
	// 全画面にしない
	if (false) Window::SetFullscreen(true);
	// 手動リサイズを許可する
	else Window::SetStyle(WindowStyle::Sizable);

	// 背景の色を設定 | Set background color
	Scene::SetBackground(ColorF{ 0.8, 1.0, 1.0 });

	// シーンと遷移時の色を設定
	MyApp manager;
	manager
		//.add<Roomlist>(State::Roomlist)
		.add<Room>(State::Room)
		.setFadeColor(ColorF{ 0.8, 1.0, 1.0 });

	while (System::Update())
	{
		recorder.SendAudioData();
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

