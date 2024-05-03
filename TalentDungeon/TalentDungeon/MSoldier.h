#pragma once
#include "Monster.h"
class MSoldier :
    public Monster
{
	static int number;
private:
	float	ChangeHPLevel;
	float	PutOnArmerTime;
	float	CurPutOnArmTime;
	int		state;
public:
	MSoldier();
	~MSoldier();

	float GetDamage() { return Damage; }

	virtual void FixedUpdate();
	virtual void Update();
	virtual void Render(HDC& _dc);

};

