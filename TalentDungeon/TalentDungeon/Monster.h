#pragma once
#include "Object.h"

namespace game
{
	class Collider;
}

class Monster : public game::Object
{
private:
	static int KillCount;
	static bool GameOverFlag;
protected:
	static gameMath::Vector3 playerPos;
	float HP;
	float MaxHP;
	float MoveSpeed;
	float Damage;

public:
	Monster();
	~Monster();

	float GetDamage() { return Damage; }


	virtual void OnCollisionEnter(game::Collider* _src);

	virtual void FixedUpdate() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC& _dc) = 0;

	static void UpdatePlayerPos(const Object* player);
	static int GetKillCount() { return KillCount; }
	static void SetGameOverFlag(bool _GameOverFlag) { GameOverFlag = _GameOverFlag; }
};

