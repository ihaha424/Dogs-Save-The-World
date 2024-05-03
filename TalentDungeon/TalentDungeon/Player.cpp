#include "Player.h"
#include "DogBowl.h"
#include "InputSystem.h"
#include "GameTime.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Collider.h"
#include "MKing.h"
#include "Monster.h"
#include "GameRender.h"
#include "SceneManager.h"

Player::Player() :AttackDelay(0), status(PlayerStatus::Default), statusTime(0),
weapon(nullptr), HP(100.0f), MaxHP(HP), MP(100.0f), DashMoveSpeed(3000.0f), SuperStateMoveSpeed(700.f),
MoveSpeed(500.0f), TrueMoveSpeed(500.0f)
{
	for (int i = 0; i < (int)Skill::End; i++)
	{
		_skillTime[i].flag = false;
		_skillTime[i].curSkillTime = 0.0f;
	}
	_skillTime[(int)Skill::Boom].SkillTime = 20.0f;
	_skillTime[(int)Skill::Penetration].SkillTime = 5.0f;



	SetObjName("Player");
	SetObjType(game::OBJECT_TYPE::PLAYER);

	textureSize = 1;
	texture = (game::Texture**)malloc(sizeof(game::Texture*) * textureSize);

	texture[0] = game::ResourceManager::GetInstance()->LoadTexture("Player1", "\\Texture\\Dogs\\Dog1.bmp");
	transform._position._x = ScreenWidth/2;
	transform._position._y = ScreenHeight/2;
	
	/*game::Scene* curScene = game::SceneManager::GetInstance()->GetCurScene();
	curScene->AddObject(weapon, game::OBJECT_TYPE::WEAPON);*/
	weapon = new DogBowl(50, 1.0f, 1000.0f);
	weapon->transform.SetRotation(transform.GetRotation());
	weapon->transform.SetPosition(transform.GetPosition());

	CreateCollider();
	collider->SetScale(gameMath::Vector3(texture[0]->Width(), texture[0]->Height(), 0));
}

Player::~Player() 
{
	delete weapon;
}

void Player::FixedUpdate() 
{
	if (weapon != nullptr)
	{
		weapon->transform.SetRotation(transform.GetRotation());
		weapon->transform.SetPosition(transform.GetPosition());
		weapon->FixedUpdate();
	}

	StatusTransForm();
	SkillCheck();
}

void Player::Update()
{
	if (HP <= 0)
	{
		_status = game::DeActive;
		if(MKing::GetBossCount() > 0)
			game::SceneManager::GetInstance()->ChangeScene(game::SCENE_TYPE::FINISH_WIN);
		else
			game::SceneManager::GetInstance()->ChangeScene(game::SCENE_TYPE::FINISH_LOSE);

	}

	AttackDelay += gameTime::DT;//

	gameMath::Vector3 pos(0, 0, 0);
	const input::MouseState& MousePos = input::InputSystem::GetInstance()->GetMouseState();
	gameMath::Vector3 dirVector(MousePos.x, MousePos.y, 0);
	dirVector = dirVector - transform.GetPosition();
	dirVector = dirVector.Nomalization();

	if (input::KEYHOLD(input::KEY::W))
	{
		pos._y -= 1;
		transform._rotation = gameMath::Vector3(0, 0, 270);
	}
	if (input::KEYHOLD(input::KEY::S))
	{
		pos._y += 1;
		transform._rotation = gameMath::Vector3(0, 0, 90);
	}
	if (input::KEYHOLD(input::KEY::A))
	{
		pos._x -= 1;
		transform._rotation = gameMath::Vector3(0, 0, 180);
	}
	if (input::KEYHOLD(input::KEY::D))
	{
		pos._x += 1;
		transform._rotation = gameMath::Vector3(0, 0, 0);
	}
	if (input::KEYHOLD(input::KEY::L_MOUSE_BUTTON))
	{
		Attack(dirVector);
	}
	if (input::KEYTAP(input::KEY::R_MOUSE_BUTTON))
	{
		if (_skillTime[(int)Skill::Penetration].flag == 0)
			_skillTime[(int)Skill::Penetration].flag = true;
	}
	if (input::KEYTAP(input::KEY::SPACE))
	{
		if (status == PlayerStatus::Default)
		{
			status = PlayerStatus::Dash;
			game::ResourceManager::GetInstance()->PlayMusic(game::eSoundList::DashEffect, game::eSoundChannel::Effect_Dash);
		}
	}

	transform._position += (pos.Nomalization() * MoveSpeed * gameTime::DT);
	CheckBoundery();
	//Weapon update
	if (weapon != nullptr)
	{
		//50은 offset하드 코딩
		weapon->transform.SetPosition(transform.GetPosition() + dirVector * (float)(texture[0]->Height()));
		weapon->transform.SetRotation(transform.GetRotation());
		weapon->Update();
	}
}

void Player::Render(HDC& _dc)
{

	if (weapon != nullptr)
	{
		weapon->Render(_dc);
	}
	if (status == PlayerStatus::SuperState)
		texture[0]->RenderAlphaTexture(_dc, transform, 60, RGB(169, 123, 139));
	else
		texture[0]->RenderTexture(_dc, transform, RGB(169, 123, 139));
	
	//HP바 Render
	//따로 UI로 뺴야함
	//전체 체력바 길이 x texture[0]->Width(), y:10, y offset: texture[0]->Height()/2 + 10
	game::GameRender::GetInstance()->DrawRectLine(
		(int)(transform._position._x - texture[0]->Width()/2)
		, (int)(transform._position._y + texture[0]->Height() / 2 + 10)
		, texture[0]->Width(), 10, RGB(255,0,0));
	//현재 체력바 길이 x texture[0]->Width(), y:10, y offset: texture[0]->Height()/2 + 10
	int curHPPercent = texture[0]->Width() * (int)HP / MaxHP;
	game::GameRender::GetInstance()->DrawRect(
		(int)(transform._position._x - texture[0]->Width()/2)
		, (int)(transform._position._y + texture[0]->Height() / 2 + 10)
		, curHPPercent, 10, RGB(255, 0, 0));

	//collider_Render
	ComponentRender(_dc);

}

void Player::Attack(gameMath::Vector3 _dirVector)
{
	//Waepon에 따라 다르게 할것
	if (weapon == nullptr)
		return;
	if (AttackDelay > weapon->GetDelayTime())
	{
		game::ResourceManager::GetInstance()->PlayMusic(game::eSoundList::ShotEffect, game::eSoundChannel::Effect_Shot);
		weapon->Attack(_dirVector);
		AttackDelay = 0;
	}
}

//충돌 처리 후 예정
void Player::SetWeapon(Weapon& _weapon)
{
	weapon = &_weapon;
}

void Player::StatusTransForm()
{
	if (status == PlayerStatus::SuperState)
	{
		statusTime += FixedUpdateTime;
		MoveSpeed = SuperStateMoveSpeed;
		if (statusTime > 1.0f)//1초
		{
			MoveSpeed = TrueMoveSpeed;
			status = PlayerStatus::Default;
			statusTime = 0;
		}
	}
	if (status == PlayerStatus::Dash)
	{
		statusTime += FixedUpdateTime;
		MoveSpeed  = DashMoveSpeed;
		if (statusTime > 0.1f)//0.05초
		{
			MoveSpeed = TrueMoveSpeed;
			status = PlayerStatus::Default;
			statusTime = 0;
		}
	}
}

int Player::GetSkillFlag(int i)
{
	return _skillTime[i].flag;
}

void Player::UpgradeDamage()
{
	weapon->SetDamage((weapon->GetDamage() + 20.0f));
}

void Player::UpgradeMoveSpeed()
{
	MoveSpeed += 100;
	TrueMoveSpeed += 100;
	DashMoveSpeed += 100;
	SuperStateMoveSpeed += 100;
}

void Player::UpgradeAKCount()
{
	weapon->SetMaxShot(weapon->GetMaxShot() + 1);
}

void Player::UpgradeAKSpeed()
{
	weapon->SetDelayTime(weapon->GetDelayTime() - 0.2f);
}

void Player::UpgradeHPHeal()
{
	HP = MaxHP;
}

void Player::SkillCheck()
{
	for (int i = 0; i < (int)Skill::End; i++)
	{
		if (_skillTime[i].flag)
		{
			_skillTime[i].curSkillTime += FixedUpdateTime;
			if (_skillTime[i].curSkillTime > _skillTime[i].SkillTime)
			{
				_skillTime[i].curSkillTime = 0;
				_skillTime[i].flag++;
			}
		}
	}
	SkillPenetration();
	SkillBoom();
}

void Player::SkillPenetration()
{
	if (_skillTime[(int)Skill::Penetration].flag == 1)
	{
		if (weapon == nullptr)
			return;
		dynamic_cast<DogBowl*>(weapon)->SetIsPenetration(true);
	}
	else
	{
		if(_skillTime[(int)Skill::Penetration].flag == 2)
			dynamic_cast<DogBowl*>(weapon)->SetIsPenetration(false);
		if (_skillTime[(int)Skill::Penetration].flag == 3)
			_skillTime[(int)Skill::Penetration].flag = 0;
	}
}

void Player::SkillBoom()
{
	if (_skillTime[(int)Skill::Boom].flag == 1)
	{
		if (weapon == nullptr)
			return;
		dynamic_cast<DogBowl*>(weapon)->SetIsPenetration(true);
	}
	else
	{
		if (_skillTime[(int)Skill::Boom].flag == 2)
			dynamic_cast<DogBowl*>(weapon)->SetIsPenetration(false);
		if (_skillTime[(int)Skill::Boom].flag == 3)
			_skillTime[(int)Skill::Boom].flag = 0;
	}
}

void Player::CheckBoundery()
{
	if (transform._position._x < 0)
		transform._position._x = 0;
	if (transform._position._x > ScreenWidth)
		transform._position._x = ScreenWidth;
	if (transform._position._y < 0)
		transform._position._y = 0;
	if (transform._position._y > 1000)
		transform._position._y = 1000;
}


void Player::OnCollisionEnter(game::Collider* _src)
{
	if (!DebugModeFlag)
	{
		if (_src->GetMyObject()->GetObjType() == game::OBJECT_TYPE::MONSTER)
		{
			if (status == PlayerStatus::Default)
			{
				game::ResourceManager::GetInstance()->PlayMusic(game::eSoundList::CollisionEffect, game::eSoundChannel::Effect_Collision);
				HP -= dynamic_cast<Monster*>(_src->GetMyObject())->GetDamage();
				status = PlayerStatus::SuperState;
				collider->OnCollisionExit(_src);
			}
		}
	}
}