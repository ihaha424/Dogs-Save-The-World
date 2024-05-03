#pragma once
#include "UI.h"

namespace gameMath
{
	class Transform;
}

class TimeUI :
    public game::UI
{
private:
	gameMath::Transform	NumberXPos[4];
	int					Number[4];
	float				Time;
public:
	TimeUI();
	~TimeUI();

	float GetTime() { return Time; }

	virtual void FixedUpdate();
	virtual void Update();
	virtual void Render(HDC& _dc);

};

