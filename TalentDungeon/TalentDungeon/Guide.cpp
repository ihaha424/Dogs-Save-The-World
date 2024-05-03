#include "Guide.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "InputSystem.h"
#include "Define.h"

Guide::Guide() : flag(0), index(0)
{
	SetObjName("Guide");
	textureSize = 2;
	texture = (game::Texture**)malloc(sizeof(game::Texture*) * textureSize);

	texture[0] = game::ResourceManager::GetInstance()->LoadTexture("Guide", "\\Texture\\UI\\Guied.bmp");
	texture[1] = game::ResourceManager::GetInstance()->LoadTexture("Guide2", "\\Texture\\UI\\Guied2.bmp");
	transform._position._x = ScreenWidth / 2;
	transform._position._y = ScreenHeight / 2;
	transform._scale._x = texture[0]->Width();
	transform._scale._y = texture[0]->Height();
}

Guide::~Guide()
{
}

void Guide::FixedUpdate()
{
}

void Guide::Update()
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
		index++;
		if (index == 2)
		{
			_status = game::Status::DeActive;
			index = 0;
		}
	}
}

void Guide::Render(HDC& _dc)
{
	texture[index]->RenderTexture(_dc, transform, RGB(255, 255, 255));
}
