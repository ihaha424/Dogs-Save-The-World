#include "Monster.h"
#include "Collider.h"
#include "Weapon.h"
#include "DieUI.h"
#include "EventManager.h"
#include "SceneManager.h"

gameMath::Vector3 Monster::playerPos = {};
int Monster::KillCount = 0;
bool Monster::GameOverFlag = false;

Monster::Monster() {}

Monster::~Monster()
{
	if (!GameOverFlag)
	{
		KillCount++;
		game::Object* obj = new DieUI(transform._position);
		game::SceneManager::GetInstance()->GetCurScene()->AddObject(obj, game::OBJECT_TYPE::UI);
		EventManager::UpKillMonsterCount();
	}
}

void Monster::UpdatePlayerPos(const Object* player)
{
	playerPos = player->transform._position;
}


void Monster::OnCollisionEnter(game::Collider* _src)
{
	if (_src->GetMyObject()->GetObjType() == game::OBJECT_TYPE::WEAPON)
	{
		Weapon* asd = dynamic_cast<Weapon*>(_src->GetMyObject());
		float asdf = asd->GetDamage();
		HP -= dynamic_cast<Weapon*>(_src->GetMyObject())->GetDamage();
		collider->OnCollisionExit(_src);
	}
	if (_src->GetMyObject()->GetObjType() == game::OBJECT_TYPE::PLAYER)
	{
		collider->OnCollisionExit(_src);
	}
}
