#pragma once

#include "Define.h"
#include "Weapon.h"

class Bone : public Weapon
{
private:
	bool	IsPenetration;
    float	moveSpeed;
	float	survivalTime;
	float	fixedTime;
	gameMath::Vector3 dir;
public:
	Bone();
	~Bone();

	void SetSurvivalTime(float _survivalTime) { survivalTime = _survivalTime; };
	void SetFixedlTime(float _fixedTime) { fixedTime = _fixedTime; };
	void SetMoveSpeed(float _moveSpeed) { moveSpeed = _moveSpeed; };
	void SetDirection(gameMath::Vector3 _dir) { dir = _dir; };
	void SetIsPenetration(bool _flag) { IsPenetration = _flag; }

	virtual void FixedUpdate();
	virtual void Update();
	virtual void Render(HDC& _dc);
	virtual void Attack(gameMath::Vector3 _dirVector);

	virtual void OnCollisionEnter(game::Collider* _src);
};

