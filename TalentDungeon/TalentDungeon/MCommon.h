#pragma once
#include "Monster.h"
class MCommon : public Monster
{
	static int number;
public:
	MCommon();
	~MCommon();

	float GetDamage() { return Damage; }

	virtual void FixedUpdate();
	virtual void Update();
	virtual void Render(HDC& _dc);

};

