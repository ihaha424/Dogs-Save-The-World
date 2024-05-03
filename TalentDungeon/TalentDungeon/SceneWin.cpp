#include "SceneWin.h"
#include "BackGround.h"
#include "WinUI.h"
#include "ResourceManager.h"


SceneWin::SceneWin()
{
}

SceneWin::~SceneWin()
{
}

void SceneWin::Enter()
{
	game::ResourceManager::GetInstance()->PlayMusic(game::eSoundList::StartBGM, game::eSoundChannel::BGM);
	game::Object* obj = new BackGround;
	AddObject(obj, game::OBJECT_TYPE::BACKGROUND);

	obj = new WinUI;
	AddObject(obj, game::OBJECT_TYPE::UI);
}

void SceneWin::Exit()
{
}
