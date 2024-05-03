#pragma once
#include "Monster.h"
class MHero :
    public Monster
{
	static int number;
private:
	float	DashTime;
	float	ReadyTime;
	float	CurDashTime;
	int		DashFlag;
	float	AnimationTime;
	float	CurAnimationTime;
	gameMath::Vector3 dirVector;

public:
	MHero();
	~MHero();

	float GetDamage() { return Damage; }

	virtual void FixedUpdate();
	virtual void Update();
	virtual void Render(HDC& _dc);
};

