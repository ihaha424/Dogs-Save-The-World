#include "MKing.h"
#include "GameTime.h"
#include "Texture.h"
#include "Collider.h"
#include "ResourceManager.h"
#include "GameRender.h"
#include "MBoomer.h"
#include "GameRandom.h"
#include "Weapon.h"
#include "SceneManager.h"
#include "EventManager.h"

int MKing::BossCount = 0;
int MKing::CurBossCount = 0;

MKing::MKing(): curTime(0), curDelayTime(0), AttackCount(0)
{
	CurBossCount++;
	HP = 3000.0f;
	MaxHP = HP;
	Damage = 10.0f;
	MoveSpeed = 100.0f;
	AttackTime = 5.0f;
	AttackDelay = 0.1f;

	SetObjName("MKing");
	SetObjType(game::OBJECT_TYPE::MONSTER);

	textureSize = 1;
	texture = (game::Texture**)malloc(sizeof(game::Texture*) * textureSize);
	texture[0] = game::ResourceManager::GetInstance()->LoadTexture("MKing", "\\Texture\\Cats\\King\\Cat_King.bmp");
	CreateCollider();
	collider->SetScale(gameMath::Vector3(texture[0]->Width(), texture[0]->Height(), 0));

	boomer = new MBoomer[arrMax];

	for (int i = 0; i < arrMax; i++)
	{
		boomer[i]._status = game::Destroy;
	}
}

MKing::~MKing()
{
	delete[] boomer;
	EventManager::UpKillMonsterCount(100);
}

void MKing::FixedUpdate()
{}

void MKing::Attack()
{
	boomer[AttackCount]._status = game::Active;
	boomer[AttackCount].transform.SetPosition(StartBoomerPosition());
	gameMath::Vector3 dirVector = playerPos - boomer[AttackCount].transform._position;
	dirVector = dirVector.Nomalization();
	boomer[AttackCount].SetHP(1.0f);
	boomer[AttackCount].SetDirection(dirVector);
	boomer[AttackCount].SetSurvivalTime(2);
	boomer[AttackCount].SetFixedlTime(0);
}

void MKing::Update()
{
	if (HP <= 0)
	{
		_status = game::Destroy;
		BossCount++;
		CurBossCount--;
		if(CurBossCount == 0)
			game::ResourceManager::GetInstance()->PlayMusic(game::eSoundList::MainBGM, game::eSoundChannel::BGM);
	}
	for (int i = 0; i < arrMax; i++)
	{
		if (boomer[i]._status == game::Active)
		{
			boomer[i].Update();
		}
	}
	if (curTime < AttackTime)
	{
		curTime += gameTime::DT;
		gameMath::Vector3 dirVector = playerPos - transform._position;
		dirVector = dirVector.Nomalization();
		transform._position += dirVector * MoveSpeed * gameTime::DT;
	}
	else
	{
		curDelayTime += gameTime::DT;
		while (curDelayTime > AttackDelay)
		{
			curDelayTime -= AttackDelay;
			Attack();
			AttackCount++;
			if (AttackCount >= arrMax)
			{
				curTime -= AttackTime;
				AttackCount = 0;
				curDelayTime = 0;
				return;
			}
		}
	}
}

void MKing::Render(HDC& _dc)
{
	texture[0]->RenderTexture(_dc, transform, RGB(169, 123, 139));
	ComponentRender(_dc);

	//HP바 Render
	//따로 UI로 뺴야함
	//전체 체력바 길이 x texture[0]->Width(), y:10, y offset: texture[0]->Height()/2 + 10
	game::GameRender::GetInstance()->DrawRectLine(
		(int)(transform._position._x - texture[0]->Width()/2)
		, (int)(transform._position._y + texture[0]->Height() / 2 + 10)
		, texture[0]->Width(), 20, RGB(255, 0, 0));
	//현재 체력바 길이 x texture[0]->Width(), y:10, y offset: texture[0]->Height()/2 + 10
	int curHPPercent = texture[0]->Width() * (int)HP / MaxHP;
	game::GameRender::GetInstance()->DrawRect(
		(int)(transform._position._x - texture[0]->Width() / 2)
		, (int)(transform._position._y + texture[0]->Height() / 2 + 10)
		, curHPPercent, 20, RGB(255, 0, 0));
	for (int i = 0; i < arrMax; i++)
	{
		if (boomer[i]._status == game::Active)
		{
			boomer[i].Render(_dc);
		}
	}
}

gameMath::Vector3 MKing::StartBoomerPosition()
{
	//생성 범위
	
	int X = game::GameRandom::GetIncetance()->RandInt(200) - 100;
	int Y = game::GameRandom::GetIncetance()->RandInt(200) - 100;
	if (X > 0)
		X = transform._position._x + 200 + X;
	else
		X = transform._position._x - 200 - X;
	if (Y > 0)
		Y = transform._position._y + 200 + Y;
	else
		Y = transform._position._y - 200 - Y;

	return gameMath::Vector3(X, Y, 0);
}
