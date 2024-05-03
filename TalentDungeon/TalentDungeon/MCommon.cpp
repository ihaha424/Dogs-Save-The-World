#include "MCommon.h"
#include "GameTime.h"
#include "Texture.h"
#include "Collider.h"
#include "ResourceManager.h"
#include <iostream>

int MCommon::number = 0;
MCommon::MCommon()
{
	HP = 100.0f;
	Damage = 10.0f;
	MoveSpeed = 400.0f;

	SetObjName("MCommon");
	SetObjType(game::OBJECT_TYPE::MONSTER);

	textureSize = 1;
	texture = (game::Texture**)malloc(sizeof(game::Texture*) * textureSize);

	number = (number + 1) % 3;
	std::string path = "\\Texture\\Cats\\Common\\Cat_Common";
	path += number + '1';
	path += ".bmp";

	std::string name = "MCommon";
	name += number + '1';

	texture[0] = game::ResourceManager::GetInstance()->LoadTexture(name.c_str(), path.c_str());
	CreateCollider();
	collider->SetScale(gameMath::Vector3(texture[0]->Width(), texture[0]->Height(), 0));
}

MCommon::~MCommon() {}

void MCommon::FixedUpdate()
{
}

void MCommon::Update()
{
	if (HP <= 0)
	{
		_status = game::Destroy;
	}
	gameMath::Vector3 dirVector = playerPos - transform._position;
	dirVector = dirVector.Nomalization();
	transform._position += dirVector * MoveSpeed * gameTime::DT;
}

void MCommon::Render(HDC& _dc)
{
	texture[0]->RenderTexture(_dc, transform, RGB(169, 123, 139));
	ComponentRender(_dc);
}
