#pragma once

#include "Define.h"
#include "Scene.h"

class TimeUI;
class EventManager;

class SceneStage01 : public game::Scene
{
private:
	TimeUI* TimeData;
	EventManager* _EventManager;
public:
	SceneStage01();
	~SceneStage01();
	virtual void Enter();
	virtual void Exit();
};

