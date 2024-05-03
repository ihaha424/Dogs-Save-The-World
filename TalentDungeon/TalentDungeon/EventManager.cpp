#include "EventManager.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "InputSystem.h"
#include "GameRandom.h"
#include "GameTime.h"
#include "Player.h"
#include "Define.h"

int EventManager::KillMonster = 0;

EventManager::EventManager() : MaxSkill{3,4,100,100,100}, ShowIndex{0,0}, Onflag(0), Exp(3)
{
	SetObjName("EventManager");
	textureSize = 5;
	texture = (game::Texture**)malloc(sizeof(game::Texture*) * textureSize);

	texture[0] = game::ResourceManager::GetInstance()->LoadTexture("AKCountUp", "\\Texture\\UI\\LevelUpUI\\AKCountUp2.bmp");
	texture[1] = game::ResourceManager::GetInstance()->LoadTexture("AKSpeedUp", "\\Texture\\UI\\LevelUpUI\\AKSpeedUp2.bmp");
	texture[2] = game::ResourceManager::GetInstance()->LoadTexture("AKUp", "\\Texture\\UI\\LevelUpUI\\AKUp2.bmp");
	texture[3] = game::ResourceManager::GetInstance()->LoadTexture("MoveSpeed", "\\Texture\\UI\\LevelUpUI\\MoveSpeed2.bmp");
	texture[4] = game::ResourceManager::GetInstance()->LoadTexture("HPHeal", "\\Texture\\UI\\LevelUpUI\\HPHeal2.bmp");

	transform._position._x = ScreenWidth / 2;
	transform._position._y = ScreenHeight / 2;
	transform._scale._x = texture[0]->Width();
	transform._scale._y = texture[0]->Height();
}

EventManager::~EventManager()
{
}

void EventManager::FixedUpdate()
{
}

void EventManager::SetLevelUpUI()
{
	if (Onflag == 0)
	{
		Onflag = 1;
		_status = game::Status::Active;
		gameTime::GameTime::GetInstance()->SetTimeScale(0.0f);
		ShowIndex[0] = game::GameRandom::GetIncetance()->RandPercent(5, MaxSkill[0] * 10, MaxSkill[1] * 10, MaxSkill[2], MaxSkill[3], MaxSkill[4]);
		while (MaxSkill[ShowIndex[0]] <= 0)
		{
			ShowIndex[0] = game::GameRandom::GetIncetance()->RandPercent(5, MaxSkill[0] * 10, MaxSkill[1] * 10, MaxSkill[2], MaxSkill[3], MaxSkill[4]);
		}
		MaxSkill[ShowIndex[0]]--;

		ShowIndex[1] = game::GameRandom::GetIncetance()->RandPercent(5, MaxSkill[0] * 10, MaxSkill[1] * 10, MaxSkill[2], MaxSkill[3], MaxSkill[4]);
		while (MaxSkill[ShowIndex[1]] <= 0 || MaxSkill[ShowIndex[1]] == MaxSkill[ShowIndex[0]])
		{
			ShowIndex[1] = game::GameRandom::GetIncetance()->RandPercent(5, MaxSkill[0] * 10, MaxSkill[1] * 10, MaxSkill[2], MaxSkill[3], MaxSkill[4]);
		}
		MaxSkill[ShowIndex[1]]--;
	}
}

void EventManager::EffectLevelUp(int index)
{
	switch (ShowIndex[index])
	{
	case 0:
		player->UpgradeAKCount();
		break;
	case 1:
		player->UpgradeAKSpeed();
		break;
	case 2:
		player->UpgradeDamage();
		break;
	case 3:
		player->UpgradeMoveSpeed();
		break;
	case 4:
		player->UpgradeHPHeal();
		break;
	default:
		//none type Monster
		break;
	}
}

void EventManager::Update()
{ 
	if (KillMonster > Exp)
	{
		LevelUpTriggrr = 1;
		if (LevelUpTriggrr)
		{
			SetLevelUpUI();
			const input::MouseState& MousePos = input::InputSystem::GetInstance()->GetMouseState();

			if (input::KEYTAP(input::KEY::L_MOUSE_BUTTON) && MousePos.x < (ScreenWidth / 2))
			{
				EffectLevelUp(0);
				_status = game::Status::UnVisible;
				gameTime::GameTime::GetInstance()->SetTimeScale(1.0f);
				Onflag = 0;
				LevelUpTriggrr = 0;
				KillMonster -= Exp;
				Exp *= 1.5;
			}
			else if(input::KEYTAP(input::KEY::L_MOUSE_BUTTON) && MousePos.x >= (ScreenWidth / 2))
			{
				EffectLevelUp(1);
				_status = game::Status::UnVisible;
				gameTime::GameTime::GetInstance()->SetTimeScale(1.0f);
				Onflag = 0;
				LevelUpTriggrr = 0;
				KillMonster -= Exp;
				Exp *= 1.5;
			}
		}
	}
}

void EventManager::Render(HDC& _dc)
{
	transform._position._x -= ScreenWidth / 4;
	texture[ShowIndex[0]]->RenderTexture(_dc, transform, RGB(255, 255, 255));
	transform._position._x += ScreenWidth / 2;
	texture[ShowIndex[1]]->RenderTexture(_dc, transform, RGB(255, 255, 255));
	transform._position._x -= ScreenWidth / 4;
}
