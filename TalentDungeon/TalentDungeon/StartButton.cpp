#include "StartButton.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Texture.h"
#include "InputSystem.h"
#include "Define.h"

StartButton::StartButton(): flag(0)
{
	SetObjName("StartButton");
	textureSize = 2;
	texture = (game::Texture**)malloc(sizeof(game::Texture*) * textureSize);

	texture[0] = game::ResourceManager::GetInstance()->LoadTexture("StartButton", "\\Texture\\UI\\StartButton.bmp");
	texture[1] = game::ResourceManager::GetInstance()->LoadTexture("StartButton2", "\\Texture\\UI\\StartButton2.bmp");
	transform._position._x = ScreenWidth - ScreenWidth / 8;
	transform._position._y = ScreenHeight - ScreenHeight / 3;
	transform._scale._x = texture[0]->Width();
	transform._scale._y = texture[0]->Height();
}

StartButton::~StartButton()
{
}

void StartButton::FixedUpdate()
{
}

void StartButton::Update()
{
	CurButtonStatus();
	if (GetButtonStatus() == ButtonStatus::EnterMouse)
	{
		flag = 1;
	}
	else if (GetButtonStatus() == ButtonStatus::ExitMouse)
	{
		flag = 0;
	}
	if (flag == 1 && input::KEYTAP(input::KEY::L_MOUSE_BUTTON))
	{
		game::SceneManager::GetInstance()->ChangeScene(game::SCENE_TYPE::STAGE_01);
	}
}

void StartButton::Render(HDC& _dc)
{
	if(flag == 0)
		texture[0]->RenderTexture(_dc, transform, RGB(255, 255, 255));
	else
		texture[1]->RenderTexture(_dc, transform, RGB(255, 255, 255));
}
