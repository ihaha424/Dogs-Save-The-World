#include "SceneStage01.h"
#include "PathManager.h"
#include "ColliderManager.h"
#include "BackGround.h"
#include "Player.h"
#include "MKing.h"
#include "Monster.h"
#include "FactoryMonster.h"
#include "Texture.h"
#include "TimeUI.h"
#include "EventManager.h"
#include "FireBoneSkillUI.h"
#include "ResourceManager.h"
#include "SharedData.h"
#include "Define.h"

SceneStage01::SceneStage01() {}

SceneStage01::~SceneStage01() {}

void SceneStage01::Enter()
{
	game::ResourceManager::GetInstance()->PlayMusic(game::eSoundList::MainBGM, game::eSoundChannel::BGM);


	game::Object* obj;
	_EventManager = new EventManager;
	obj = _EventManager;
	obj->SetObjStatus(game::Status::UnVisible);
	AddObject(obj, game::OBJECT_TYPE::EventManager);

	obj = new BackGround;
	AddObject(obj, game::OBJECT_TYPE::BACKGROUND);


	Player* player = new Player;
	_EventManager->SetPlayer(player);
	obj = player;
	AddObject(obj, game::OBJECT_TYPE::PLAYER);

	obj = new FactoryMonster();
	AddObject(obj, game::OBJECT_TYPE::FACTORY);

	TimeData = new TimeUI();
	obj = TimeData;
	AddObject(obj, game::OBJECT_TYPE::UI);

	obj = new FireBoneSkillUI();
	AddObject(obj, game::OBJECT_TYPE::UI);

	game::ColliderManager::GetInstance()->CheckGourp(game::OBJECT_TYPE::WEAPON, game::OBJECT_TYPE::MONSTER);
	game::ColliderManager::GetInstance()->CheckGourp(game::OBJECT_TYPE::PLAYER, game::OBJECT_TYPE::MONSTER);
}

void SceneStage01::Exit()
{
	SharedData::GetInstance()->SetSharedDataTime(TimeData->GetTime());
	SharedData::GetInstance()->SetKillCount(Monster::GetKillCount());
	SharedData::GetInstance()->SetKillBossCount(MKing::GetBossCount());
	Monster::SetGameOverFlag(true);

	//충돌 그룹 해제
	game::ColliderManager::GetInstance()->ResetGourp();
}
