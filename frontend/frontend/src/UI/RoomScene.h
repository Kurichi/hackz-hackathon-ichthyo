#pragma once
#include <Siv3D.hpp>
#include "Scene.h"

// 部屋シーン(ここで通話する)
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
