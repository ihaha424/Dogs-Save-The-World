#include "SceneStart.h"
#include "StartUI.h"
#include "StartButton.h"
#include "GuideButton.h"
#include "Guide.h"
#include "Title.h"
#include "ResourceManager.h"
#include "Define.h"

SceneStart::SceneStart() {}

SceneStart::~SceneStart() {}

void SceneStart::Enter()
{
	game::ResourceManager::GetInstance()->PlayMusic(game::eSoundList::StartBGM, game::eSoundChannel::BGM);

	game::Object* obj = new StartUI;
	AddObject(obj, game::OBJECT_TYPE::BACKGROUND);

	obj = new StartButton;
	AddObject(obj, game::OBJECT_TYPE::UI);


	obj = new GuideButton;
	AddObject(obj, game::OBJECT_TYPE::UI);

	obj = new Title;
	AddObject(obj, game::OBJECT_TYPE::UI);

	obj = new Guide;
	obj->SetObjStatus(game::Status::DeActive);
	AddObject(obj, game::OBJECT_TYPE::UI);
}

void SceneStart::Exit() {}
