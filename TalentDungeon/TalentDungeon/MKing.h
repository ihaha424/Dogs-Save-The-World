#pragma once
#include "Monster.h"

class MBoomer;

class MKing :
    public Monster
{
private:
	static int BossCount;
	static int CurBossCount;
	const int arrMax = 10;
	float	AttackTime;
	float	curTime;
	float	AttackDelay;
	float	curDelayTime;
	int		AttackCount;
	MBoomer* boomer;
public:
	MKing();
	~MKing();

	float GetDamage() { return Damage; }
	void Attack();

	static int GetBossCount() { return BossCount; };
	gameMath::Vector3 StartBoomerPosition();

	virtual void FixedUpdate();
	virtual void Update();
	virtual void Render(HDC& _dc);
};

