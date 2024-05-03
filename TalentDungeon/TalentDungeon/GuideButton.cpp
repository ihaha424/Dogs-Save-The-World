#include "GuideButton.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "InputSystem.h"
#include "SceneManager.h"
#include "Define.h"

GuideButton::GuideButton() : flag(0)
{
	SetObjName("GuideButton");
	textureSize = 2;
	texture = (game::Texture**)malloc(sizeof(game::Texture*) * textureSize);

	texture[0] = game::ResourceManager::GetInstance()->LoadTexture("GuideButton", "\\Texture\\UI\\GuideButton.bmp");
	texture[1] = game::ResourceManager::GetInstance()->LoadTexture("GuideButton2", "\\Texture\\UI\\GuideButton2.bmp");
	transform._position._x = ScreenWidth - ScreenWidth / 8;
	transform._position._y = ScreenHeight - ScreenHeight / 6;
	transform._scale._x = texture[0]->Width();
	transform._scale._y = texture[0]->Height();
}

GuideButton::~GuideButton()
{
}

void GuideButton::FixedUpdate()
{
}

void GuideButton::Update()
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
		game::SceneManager::GetInstance()->GetCurScene()->GetObjectSrc(game::OBJECT_TYPE::UI, "Guide")->SetObjStatus(game::Status::Active);
	}
}

void GuideButton::Render(HDC& _dc)
{
	if (flag == 0)
		texture[0]->RenderTexture(_dc, transform, RGB(255, 255, 255));
	else
		texture[1]->RenderTexture(_dc, transform, RGB(255, 255, 255));
}
