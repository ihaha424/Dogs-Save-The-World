#include "MHero.h"
#include "GameTime.h"
#include "Texture.h"
#include "Collider.h"
#include "ResourceManager.h"
#include <iostream>

int MHero::number = 0;
MHero::MHero(): CurDashTime(0), DashFlag(0), CurAnimationTime(0)
{
	HP = 200.0f;
	Damage = 20.0f;
	MoveSpeed = 300.0f;
	DashTime = 3.0f;
	ReadyTime = 2.0f;
	AnimationTime = 0.1f;

	SetObjName("MHero");
	SetObjType(game::OBJECT_TYPE::MONSTER);

	textureSize = 5;
	texture = (game::Texture**)malloc(sizeof(game::Texture*) * textureSize);
	
	number = (number + 1) % 3;
	std::string path = "\\Texture\\Cats\\Hero\\Cat_Hero";
	path += number + '1';
	path += ".bmp";

	std::string name = "MHero";
	name += number + '1';

	texture[0] = game::ResourceManager::GetInstance()->LoadTexture(name.c_str(), path.c_str());
	texture[1] = game::ResourceManager::GetInstance()->LoadTexture("MHeroFire1_1", "\\Texture\\Cats\\Hero\\HeroFire1_1.bmp");
	texture[2] = game::ResourceManager::GetInstance()->LoadTexture("MHeroFire1_2", "\\Texture\\Cats\\Hero\\HeroFire1_2.bmp");
	texture[3] = game::ResourceManager::GetInstance()->LoadTexture("MHeroFire1_3", "\\Texture\\Cats\\Hero\\HeroFire1_3.bmp");
	texture[4] = game::ResourceManager::GetInstance()->LoadTexture("MHeroFire1_4", "\\Texture\\Cats\\Hero\\HeroFire1_4.bmp");
	CreateCollider();
	collider->SetScale(gameMath::Vector3(texture[0]->Width(), texture[0]->Height(), 0));
}

MHero::~MHero() {}

void MHero::FixedUpdate(){}

void MHero::Update()
{
	if (HP <= 0)
	{
		_status = game::Destroy;
	}
	CurDashTime += gameTime::DT;
	if (CurDashTime < ReadyTime)
	{
		dirVector = playerPos - transform._position;
		return;
	}
	else if (CurDashTime < DashTime)
	{
		CurAnimationTime += gameTime::DT;
		if (CurAnimationTime > AnimationTime)
		{
			DashFlag = (DashFlag + 1) % 4 + 1;
			CurAnimationTime = 0;
		}
		MoveSpeed += 5.0f;
		dirVector = dirVector.Nomalization();
		transform._position += dirVector * MoveSpeed * gameTime::DT;
	}
	else
	{
		CurDashTime = 0;
		DashFlag = 0;
		MoveSpeed = 500.0f;
	}

}

void MHero::Render(HDC& _dc)
{
	if (DashFlag)
	{
		transform._position._y -= 40;
		texture[DashFlag]->RenderTexture(_dc, transform, RGB(0, 0, 0));
		transform._position._y += 40;
	}
	texture[0]->RenderTexture(_dc, transform, RGB(169, 123, 139));
	ComponentRender(_dc);
}
