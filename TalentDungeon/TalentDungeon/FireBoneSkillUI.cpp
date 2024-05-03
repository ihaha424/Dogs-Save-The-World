#include "FireBoneSkillUI.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Texture.h"
#include "Player.h"

FireBoneSkillUI::FireBoneSkillUI()
{
	SetObjName("FireBoneSkillUI");
	textureSize = 11;
	texture = (game::Texture**)malloc(sizeof(game::Texture*) * textureSize);

	texture[0] = game::ResourceManager::GetInstance()->LoadTexture("Number0", "\\Texture\\Number\\Number0.bmp");
	texture[1] = game::ResourceManager::GetInstance()->LoadTexture("Number1", "\\Texture\\Number\\Number1.bmp");
	texture[2] = game::ResourceManager::GetInstance()->LoadTexture("Number2", "\\Texture\\Number\\Number2.bmp");
	texture[3] = game::ResourceManager::GetInstance()->LoadTexture("Number3", "\\Texture\\Number\\Number3.bmp");
	texture[4] = game::ResourceManager::GetInstance()->LoadTexture("Number4", "\\Texture\\Number\\Number4.bmp");
	texture[5] = game::ResourceManager::GetInstance()->LoadTexture("Number5", "\\Texture\\Number\\Number5.bmp");
	texture[6] = game::ResourceManager::GetInstance()->LoadTexture("Number6", "\\Texture\\Number\\Number6.bmp");
	texture[7] = game::ResourceManager::GetInstance()->LoadTexture("Number7", "\\Texture\\Number\\Number7.bmp");
	texture[8] = game::ResourceManager::GetInstance()->LoadTexture("Number8", "\\Texture\\Number\\Number8.bmp");
	texture[9] = game::ResourceManager::GetInstance()->LoadTexture("Number9", "\\Texture\\Number\\Number9.bmp");

	texture[10] = game::ResourceManager::GetInstance()->LoadTexture("FireBoneSkillUI", "\\Texture\\UI\\FireBoneSkillUI.bmp");

	transform._position._x = ScreenWidth - ScreenWidth / 8;
	transform._position._y = ScreenHeight - ScreenHeight / 4;
	transform._scale._x = texture[10]->Width();
	transform._scale._y = texture[10]->Height();
}

FireBoneSkillUI::~FireBoneSkillUI()
{
}

void FireBoneSkillUI::FixedUpdate()
{
}

void FireBoneSkillUI::Update()
{
}

void FireBoneSkillUI::Render(HDC& _dc)
{
	int Cooltime = dynamic_cast<Player*>(game::SceneManager::GetInstance()->GetCurScene()->GetObjectSrc(game::OBJECT_TYPE::PLAYER, "Player"))->GetSkillFlag(1);
	if (Cooltime != 0)
	{
		texture[10]->RenderAlphaTexture(_dc, transform, 50, RGB(255, 255, 255));
	}
	else
		texture[10]->RenderAlphaTexture(_dc, transform, 200, RGB(255, 255, 255));
}
