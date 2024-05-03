#include "MSoldier.h"
#include "GameTime.h"
#include "Texture.h"
#include "Collider.h"
#include "ResourceManager.h"
#include <iostream>


int MSoldier::number = 0;
MSoldier::MSoldier() : state(0), CurPutOnArmTime(0)
{
	HP = 150.0f;
	Damage = 20.0f;
	MoveSpeed = 500.0f;
	ChangeHPLevel = HP / 3;
	PutOnArmerTime = 3;

	SetObjName("MSoldier");
	SetObjType(game::OBJECT_TYPE::MONSTER);

	textureSize = 2;
	texture = (game::Texture**)malloc(sizeof(game::Texture*) * textureSize);
	
 	number = (number + 1) % 3;
	std::string path = "\\Texture\\Cats\\Soldier\\Cat_Soldier";
	path += number + '1';
	path += ".bmp";

	std::string name = "MSoldier";
	name += number + '1';

	texture[0] = game::ResourceManager::GetInstance()->LoadTexture(name.c_str(), path.c_str());


	path = "\\Texture\\Cats\\Soldier\\Cat_Soldier";
	path += number + '1';
	path += "_2.bmp";

	name = "MSoldier";
	name += number + '1';
	name += "_2";

	texture[1] = game::ResourceManager::GetInstance()->LoadTexture(name.c_str(), path.c_str());
	CreateCollider();
	collider->SetScale(gameMath::Vector3(texture[0]->Width(), texture[0]->Height(), 0));
}

MSoldier::~MSoldier() {}

void MSoldier::FixedUpdate() {}

void MSoldier::Update()
{
	if (HP <= 0)
	{
		_status = game::Destroy;
	}
	if (HP <= ChangeHPLevel)
	{
		state = 1;
		MoveSpeed = 200.0f;
		CurPutOnArmTime += gameTime::DT;
	}
	if (CurPutOnArmTime > PutOnArmerTime)
	{
		state = 0;
		HP = ChangeHPLevel * 3;
		MoveSpeed = 500.0f;
		CurPutOnArmTime = 0;
	}
	gameMath::Vector3 dirVector = playerPos - transform._position;
	dirVector = dirVector.Nomalization();
	transform._position += dirVector * MoveSpeed * gameTime::DT;
}

void MSoldier::Render(HDC& _dc)
{
	texture[state]->RenderTexture(_dc, transform, RGB(169, 123, 139));
	ComponentRender(_dc);
}
