#pragma once

#include "Scene.h"
class SceneStart :
    public game::Scene
{
public:
	SceneStart();
	~SceneStart();
	virtual void Enter();
	virtual void Exit();
};

