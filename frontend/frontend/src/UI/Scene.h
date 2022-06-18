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
};

// シーン管理クラス
using MyApp = SceneManager<State, Data>;
