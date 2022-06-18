#pragma once
#include <Siv3D.hpp>

// シーン管理等

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
	int32 currentUserID = 0;
	Array<String> srclist = {
		U"example/siv3d-kun.png",
		U"example/siv3d-kun.png",
		U"example/siv3d-kun.png",
		U"example/siv3d-kun.png",
		U"example/siv3d-kun.png",
		U"example/siv3d-kun.png",
		U"example/siv3d-kun.png",
		U"example/siv3d-kun.png",
		U"example/siv3d-kun.png",
		U"example/siv3d-kun.png",
		U"example/siv3d-kun.png",
		U"example/siv3d-kun.png"
	};
	Array<String> namelist = {
		U"名無し0",
		U"名無し1",
		U"名無し2",
		U"名無し3",
		U"名無し4",
		U"名無し5",
		U"名無し6",
		U"名無し7",
		U"名無し8",
		U"名無し9",
		U"名無しA",
		U"名無しB"
	};
	bool sIn = true;
	bool sOut = true;
};

// シーン管理クラス
using MyApp = SceneManager<State, Data>;
