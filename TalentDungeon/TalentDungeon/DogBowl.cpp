#include "DogBowl.h"
#include "Bone.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Collider.h"
#include "InputSystem.h"
#include "Vector3.h"

#include <iostream>

#pragma comment(lib, "Msimg32.lib")

DogBowl::DogBowl(float _damage, float _delayTime, float _bulletSpeed) :
	Weapon(_damage, _delayTime), bulletSpeed(_bulletSpeed), 
	curIndex(0), bullet(nullptr), IsPenetration(false)
{
	transform._scale /= 2;

	textureSize = 1;
	texture = (game::Texture**)malloc(sizeof(game::Texture*) * textureSize);
	
	texture[0] = game::ResourceManager::GetInstance()->LoadTexture("DogBowl", "\\Texture\\Weapon\\DogBowl.bmp");

	bullet = new Bone[arrMax];

	for (int i = 0; i < arrMax; i++)
	{
		bullet[i].SetDamage(damage);
		bullet[i].SetDelayTime(5);
		bullet[i].SetMoveSpeed(bulletSpeed);
		bullet[i]._status = game::DeActive;
	}
}

DogBowl::~DogBowl()
{
	delete[] bullet;
}

void DogBowl::FixedUpdate()
{
	for (int i = 0; i < arrMax; i++)
	{
		if (bullet[i]._status == game::Active)
		{
			bullet[i].FixedUpdate();
		}
	}
}

void DogBowl::Update()
{
}

void DogBowl::Render(HDC& _dc)
{
	texture[0]->RenderTexture(_dc, transform, RGB(255, 174, 201));
	for (int i = 0; i < arrMax; i++)
	{
		if (bullet[i]._status == game::Active)
		{
			bullet[i].Render(_dc);
		}
	}
}

void DogBowl::Attack(gameMath::Vector3 _dirVector)
{
	for (int i = 0; i < MaxShot; i++)
	{
		//Delay time
		bullet[curIndex]._status = game::Active;
		//방향설정
		bullet[curIndex].SetDirection(_dirVector);
		bullet[curIndex].transform.SetPosition(transform.GetPosition() + (i * 50));
		bullet[curIndex].SetSurvivalTime(3);
		bullet[curIndex].SetFixedlTime(0);
		bullet[curIndex].SetDamage(damage);
		if (IsPenetration)
			bullet[curIndex].SetIsPenetration(true);
		else
			bullet[curIndex].SetIsPenetration(false);
		curIndex = (curIndex + 1) % arrMax;
	}
}
