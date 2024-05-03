
#pragma once
#include "Weapon.h"

class Bone;

class DogBowl : public Weapon
{
private:
	const int arrMax = 30;
	int		curIndex;
	float bulletSpeed;
	Bone *bullet;

	bool	IsPenetration;
public:
	DogBowl(float _damage, float _delayTime, float _bulletSpeed);
	~DogBowl();

	void SetIsPenetration(bool _flag) { IsPenetration  = _flag;}


	virtual void FixedUpdate();
	virtual void Update();
	virtual void Render(HDC& _dc);
	virtual void Attack(gameMath::Vector3 _dirVector);
};

