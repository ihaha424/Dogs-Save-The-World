#include "MBoomer.h"
#include "GameTime.h"
#include "Texture.h"
#include "Collider.h"
#include "ResourceManager.h"

MBoomer::MBoomer()
{
	HP = 1.0f;
	Damage = 5.0f;
	MoveSpeed = 700.0f;

	SetObjName("MBoomer");
	SetObjType(game::OBJECT_TYPE::MONSTER);

	textureSize = 1;
	texture = (game::Texture**)malloc(sizeof(game::Texture*) * textureSize);
	texture[0] = game::ResourceManager::GetInstance()->LoadTexture("MBoomer", "\\Texture\\Cats\\King\\Cat_Boomer.bmp");
	CreateCollider();
	collider->SetScale(gameMath::Vector3(texture[0]->Width(), texture[0]->Height(), 0));
}

MBoomer::~MBoomer()
{}

void MBoomer::FixedUpdate()
{}

void MBoomer::Update()
{
	survivalTime -= gameTime::DT;
	if (survivalTime < 0 || HP <= 0)
	{
		_status = game::DeActive;
		return;
	}
	transform._position += dir * MoveSpeed * gameTime::DT;
}

void MBoomer::Render(HDC& _dc)
{
	texture[0]->RenderTexture(_dc, transform, RGB(32, 32, 64));
	ComponentRender(_dc);
}
