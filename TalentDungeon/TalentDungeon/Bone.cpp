#include "Bone.h"
#include "Collider.h"
#include "ResourceManager.h"
#include "Texture.h"

Bone::Bone() :Weapon(0, 0), IsPenetration(false)
{
	SetObjName("Bone");
	SetObjType(game::OBJECT_TYPE::WEAPON);
	_status = game::DeActive;

	textureSize = 2;
	texture = (game::Texture**)malloc(sizeof(game::Texture*) * textureSize);
	texture[0] = game::ResourceManager::GetInstance()->LoadTexture("Bone", "\\Texture\\Weapon\\Bone.bmp");
	texture[1] = game::ResourceManager::GetInstance()->LoadTexture("FireBone", "\\Texture\\Weapon\\Fire_Bone.bmp");
	CreateCollider();
	collider->SetScale(gameMath::Vector3(texture[0]->Width(), texture[0]->Height(), 0));
}

Bone::~Bone()
{
}

void Bone::FixedUpdate()
{
	fixedTime += FixedUpdateTime;
	survivalTime -= (float)(FixedUpdateTime);
	if (survivalTime < 0)
	{
		_status = game::DeActive;
		return;
	}
	gameMath::Vector3 pos = transform.GetPosition();
	pos += dir * (float)(moveSpeed * (float)(FixedUpdateTime));

	transform.SetPosition(pos);
}

void Bone::Update()
{

}

void Bone::Render(HDC& _dc)
{
	if (IsPenetration)
	{
		texture[1]->RenderTexture(_dc, transform, RGB(255, 255, 255));
	}
	texture[0]->RenderTexture(_dc, transform, RGB(255, 174, 201));
	ComponentRender(_dc);
}

void Bone::Attack(gameMath::Vector3 _dirVector) {}

void Bone::OnCollisionEnter(game::Collider* _src)
{
	if (_src->GetMyObject()->GetObjType() == game::OBJECT_TYPE::MONSTER)
	{
		if (!IsPenetration)
		{
			_status = game::DeActive;
			collider->OnCollisionExit(_src);
		}
	}
}
