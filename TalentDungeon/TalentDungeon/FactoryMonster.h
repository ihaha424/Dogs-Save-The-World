#pragma once
#include "Object.h"
class Monster;
class FactoryMonster : public game::Object
{
private:
	enum class EnemyType
	{
		Common,
		Soldier,
		Hero,
		King,
		END
	};
	unsigned int EnemyPercent[(int)EnemyType::END];

	int LevelUpTime;
	int Respontime;
	float fixedTime;
	float Second;

	int MinMonsterCount;
	int MaxMonsterCount;
	int MaxMonsterCountLine;
	int BossCount;

private:
	void LevelIncrease();

public:
	FactoryMonster();
	~FactoryMonster();

	void CreateMonster(EnemyType _type);
	void SetResponTime(int _Respontime) { Respontime = _Respontime; }
	gameMath::Vector3 StartMonsterPosition();

	virtual void FixedUpdate();
	virtual void Update();
	virtual void Render(HDC& _dc);


};

