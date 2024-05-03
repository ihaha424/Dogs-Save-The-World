#pragma once
#include "Object.h"

class Weapon;


class Player : public game::Object
{
private:
	enum class PlayerStatus
	{
		Default,
		SuperState,
		Dash
	};
	enum class Skill
	{
		Boom,
		Penetration, //관통
		End
	};
	struct SkillTime
	{
		int flag;
		float curSkillTime;
		float SkillTime;
	};

	Weapon* weapon;
	
	float HP;
	float MaxHP;
	float MP;
	float MoveSpeed;
	float TrueMoveSpeed;
	float DashMoveSpeed;
	float SuperStateMoveSpeed;
	//....이후 직업에 따라 변경?

	float AttackDelay;
	PlayerStatus status;
	float statusTime;

	SkillTime _skillTime[(int)Skill::End];

private:
	void Attack(gameMath::Vector3 _dirVector);
	void SetWeapon(Weapon& _weapon);
	void StatusTransForm();
	void SkillCheck();
	void SkillPenetration();
	void SkillBoom();
	void CheckBoundery();

public:
	Player();
	~Player();

	int GetSkillFlag(int i);
	void UpgradeAKCount();
	void UpgradeAKSpeed();
	void UpgradeDamage();
	void UpgradeMoveSpeed();
	void UpgradeHPHeal();

	virtual void FixedUpdate();
	virtual void Update();
	virtual void Render(HDC& _dc);

	virtual void OnCollisionEnter(game::Collider* _src);
};

