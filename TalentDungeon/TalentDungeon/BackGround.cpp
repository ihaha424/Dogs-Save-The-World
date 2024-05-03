#include "BackGround.h"
#include "ResourceManager.h"
#include "Texture.h"

BackGround::BackGround()
{
	SetObjName("BackGround");
	SetObjType(game::OBJECT_TYPE::BACKGROUND);

	textureSize = 1;
	texture = (game::Texture**)malloc(sizeof(game::Texture*) * textureSize);
	texture[0] = game::ResourceManager::GetInstance()->LoadTexture("BackGround", "\\Texture\\BackGround\\BackGround.bmp");
	transform.SetPosition(gameMath::Vector3(ScreenWidth/2, ScreenHeight/2, 0));
}

BackGround::~BackGround() {}

void BackGround::FixedUpdate() {}

void BackGround::Update() {}

void BackGround::Render(HDC& _dc)
{
	texture[0]->RenderTexture(_dc, transform, RGB(0, 0, 0));
}
