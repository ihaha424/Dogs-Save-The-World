#include "SceneLose.h"
#include "BackGround.h"
#include "LoseUI.h"
#include "ResourceManager.h"




SceneLose::SceneLose()
{
}

SceneLose::~SceneLose()
{
}

void SceneLose::Enter()
{
	game::ResourceManager::GetInstance()->PlayMusic(game::eSoundList::StartBGM, game::eSoundChannel::BGM);

	game::Object* obj = new BackGround;
	AddObject(obj, game::OBJECT_TYPE::BACKGROUND);

	obj = new LoseUI;
	AddObject(obj, game::OBJECT_TYPE::UI);
}

void SceneLose::Exit()
{
}
