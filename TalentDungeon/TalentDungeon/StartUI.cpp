#include "StartUI.h"
#include "ResourceManager.h"
#include "Texture.h"

StartUI::StartUI()
{
	SetObjName("BackGround");
	SetObjType(game::OBJECT_TYPE::BACKGROUND);

	textureSize = 1;
	texture = (game::Texture**)malloc(sizeof(game::Texture*) * textureSize);
	texture[0] = game::ResourceManager::GetInstance()->LoadTexture("StartUI", "\\Texture\\BackGround\\StartUI.bmp");
	transform.SetPosition(gameMath::Vector3(ScreenWidth / 2, ScreenHeight / 2, 0));
}

StartUI::~StartUI() {}

void StartUI::FixedUpdate() {}

void StartUI::Update() {}

void StartUI::Render(HDC& _dc)
{
	texture[0]->RenderTexture(_dc, transform, RGB(0, 0, 0));
}
