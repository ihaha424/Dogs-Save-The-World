#pragma once
#include "Monster.h"
class MBoomer :
    public Monster
{
private:
	float	survivalTime;
	float	fixedTime;
	gameMath::Vector3 dir;
public:
	MBoomer();
	~MBoomer();

	float GetDamage() { return Damage; }
	void SetHP(float _HP) { HP = _HP; }
	void SetSurvivalTime(float _survivalTime) { survivalTime = _survivalTime; };
	void SetFixedlTime(float _fixedTime) { fixedTime = _fixedTime; };
	void SetDirection(gameMath::Vector3 _dir) { dir = _dir; };

	virtual void FixedUpdate();
	virtual void Update();
	virtual void Render(HDC& _dc);
};

