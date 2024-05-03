#pragma once
#include "Button.h"
class WinUI :
    public game::Button
{
private:
	gameMath::Transform	NumberXPos[9];
	int					Number[9];
	float				Time;
	int					flag;
	int					KillCount;
	int					KillBossCount;

public:
	WinUI();
	~WinUI();

	virtual void FixedUpdate();
	virtual void Update();
	virtual void Render(HDC& _dc);
};

