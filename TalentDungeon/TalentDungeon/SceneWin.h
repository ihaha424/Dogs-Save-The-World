#pragma once
#include "Scene.h"
class SceneWin :
    public game::Scene
{
public:
	SceneWin();
	~SceneWin();
	virtual void Enter();
	virtual void Exit();
};

