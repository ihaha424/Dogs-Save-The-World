#pragma once
#include "UI.h"

namespace gameMath
{
	class Vetor3;
}

class DieUI :
    public game::UI
{
private:
	float	survivalTime;

public:
	DieUI(gameMath::Vector3 pos);
	~DieUI();

	virtual void FixedUpdate();
	virtual void Update();
	virtual void Render(HDC& _dc);
};

