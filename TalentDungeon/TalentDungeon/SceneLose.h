#pragma once
#include "Scene.h"
class SceneLose :
    public game::Scene
{
public:
	SceneLose();
	~SceneLose();
	virtual void Enter();
	virtual void Exit();
};

