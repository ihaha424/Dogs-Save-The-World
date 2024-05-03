#pragma once
#include "Button.h"
class LoseUI :
    public game::Button
{
private:
	gameMath::Transform	NumberXPos[8];
	int					Number[8];
	float				Time;
	int					flag;
	int					KillCount;

public:
	LoseUI();
	~LoseUI();

	virtual void FixedUpdate();
	virtual void Update();
	virtual void Render(HDC& _dc);
};

