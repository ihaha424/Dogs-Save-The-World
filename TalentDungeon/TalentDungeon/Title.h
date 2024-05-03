#pragma once
#include "UI.h"
class Title :
    public game::UI
{
public:
	Title();
	~Title();

	virtual void FixedUpdate();
	virtual void Update();
	virtual void Render(HDC& _dc);
};

