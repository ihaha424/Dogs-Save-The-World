#pragma once
#include "Object.h"

namespace game
{
	class Collider;
}

class Weapon : public game::Object
{
protected:
	float damage;
	float delayTime;
	int		MaxShot;

public:
	Weapon(float _damage, float _delayTime);
	virtual ~Weapon();

	void SetDamage(float _damage) { damage = _damage; };
	float GetDamage() { return damage; };
	void SetDelayTime(float _delayTime) {delayTime = _delayTime;}
	float GetDelayTime() { return delayTime; }
	void SetMaxShot(float _MaxShot) { MaxShot = _MaxShot; }
	float GetMaxShot() { return MaxShot; }

	virtual void FixedUpdate() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC& _dc) = 0;
	virtual void Attack(gameMath::Vector3 _dirVector) = 0;
};

